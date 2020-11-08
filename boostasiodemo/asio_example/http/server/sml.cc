

#include <boost/sml.hpp>


struct StateMachine {
  explicit StateMachine(Test* Test) : Test_(Test) {}

  auto operator()() noexcept {
    auto account_info_ready = [this] {
      return Test_->session_.AccountInfoReady();
    };

    auto can_start = [this](const Start& e) { return CanStart(e); };
    auto can_restart = [this](const Restart& e) { return CanStart(e); };

    // clang-format off
    return boost::sml::make_transition_table(
       *"Power Off"_s     + event<Start>          [ can_start ]                                                   = "Connecting"_s,
        "Power Off"_s     + event<Restart>        [ can_restart ]                                                 = "Connecting"_s,
        "Power Off"_s     + "Send"_e              / [this] { FailAllCachedTransaction(); },
        "Connecting"_s    + "ManualConnect"_e     / [this] { MayRaceImmediately(); },
        "Connecting"_s    + event<Connected>      / [this](const auto& e) { OnConnected(e); }                     = "Connected"_s,
        "Connecting"_s    + "Shutdown"_e          / [this] { StopRace(); }                                        = "Power Off"_s,
        "Connected"_s     + event<Disconnected>   / [this](const auto& e) { OnBackward(e.code); }                 = "Connecting"_s,
        "Connected"_s     [ account_info_ready ]  / [this] { Register(); }                                        = "Registering"_s,
        "Connected"_s     + "Shutdown"_e          / [this] { StopRace(); Disconnect(); }                          = "Power Off"_s,
        "Registering"_s   + "Registered"_e                                                                        = "Online"_s,
        "Registering"_s   + event<RegisterFailed> / [this](const auto& e) { Disconnect(); OnBackward(e.code); }   = "Connecting"_s,
        "Registering"_s   + "Unregister"_e        / defer,
        "Registering"_s   + "Shutdown"_e          / [this] { StopRace(); Disconnect(); }                          = "Power Off"_s,
        "Online"_s        + event<Disconnected>   / [this](const auto& e) { OnOffline(e.code); }                  = "Connecting"_s,
        "Online"_s        + "Unregister"_e        / [this](const auto& e) { OnOffline(TestError::kLogout); }     = "Unregistering"_s,
        "Online"_s        + "Shutdown"_e          / defer,
        "Online"_s        + event<Restart>        / defer,
        "Online"_s        + "Send"_e              / [this] { SendCachedTransactions(); },
        "Online"_s        + event<HeartbeatEvent> / [this](const auto& e) { Heartbeat(e.reason); },
        "Unregistering"_s + "Unregister Done"_e                                                                   = "Connected"_s,
        "Unregistering"_s + "Shutdown"_e          / defer,
        "Unregistering"_s + event<Restart>        / defer,

        "Registering"_s   + event<Disconnected>   / [] { assert(false); }                                         = "Connecting"_s,
        "Unregistering"_s + event<Disconnected>   / [] { assert(false); }                                         = "Connecting"_s,

        "Power Off"_s     + on_entry<_>           / [this] { FailAllCachedTransaction(); OnShutdown(); },
        "Connecting"_s    + on_entry<_>           / [this] { StartOrContinueRace(); },
        "Unregistering"_s + on_entry<_>           / [this] { Unregister(); },
        "Online"_s        + on_entry<_>           / [this] { StopRace(); Heartbeat("heartbeat"); OnOnline(); },
        "Online"_s        + on_exit<_>            / [this] { CancelHeartbeat(); }
      );
    // clang-format on
  }

  bool CanStart(const StartupBase& e) {
    Test_->session_.SetUserID(e.uid);
    Test_->session_.SetServiceToken(e.service_token);
    Test_->session_.SetServiceSecurity(e.service_security);

    if (Test_->session_.AccountInfoReady()) {
      return true;

    } else {
      for (auto listener : Test_->online_listeners_)
        if (auto locked_listener = listener.lock())
          locked_listener->OnLoginFailed(TestError::kInvalidAccountInfo);

      return false;
    }
  }

  void StartOrContinueRace() {
    Test_->connection_generator_->StartOrContinueRace();
  }

  void StopRace() { Test_->connection_generator_->StopRace(); }

  void MayRaceImmediately() {
    Test_->connection_generator_->MayRaceImmediately();
  }

  void OnConnected(const Connected& e) {
    Test_->connection_ = e.connection;
    Test_->connection_->SetDelegate(Test_->weak_from_this());
  }

  void Disconnect() {
    if (Test_->connection_) {
      Test_->connection_->SetDelegate({});
      Test_->connection_->Finalise();
      Test_->connection_.reset();
    }
  }

  void Register() {
    Test_->connection_->Register([=](std::error_code code) {
      if (code) {
        KwaiLogger::Error("Register failed with code {}[{}]", CODE);

        for (auto listener : Test_->online_listeners_)
          if (auto locked_listener = listener.lock())
            locked_listener->OnLoginFailed(code);

        if (INNER_SM) INNER_SM->process_event(RegisterFailed{code});

      } else {
        KwaiLogger::Info("Register succeeded.");
        if (INNER_SM) INNER_SM->process_event("Registered"_e());
      }
    });
  }

  void Unregister() {
    Test_->connection_->Unregister([=](std::error_code code) {
      KwaiLogger::Info("Unregister done with code {}[{}]", CODE);
      Test_->session_.ClearAccountInfo();
      if (INNER_SM) INNER_SM->process_event("Unregister Done"_e());
    });
  }

  void Heartbeat(const std::string& reason) {
    CancelHeartbeat();

    if (Test_->connection_)
      Test_->connection_->Heartbeat(reason, [=](auto code) {
        PrintDebugInfo();
        ScheduleHeartbeat();
      });

    // TODO(Lynn) Shall we try connect if not connected?
  }

  void ScheduleHeartbeat() {
    CancelHeartbeat();

    heartbeat_timer_ =
        Test_->Queue()->PostAfter(Test_->Config()->HeartbeatInterval(),
                                   &StateMachine::Heartbeat, this, "heartbeat");
  }

  void CancelHeartbeat() {
    if (heartbeat_timer_.IsValid()) Test_->Queue()->Cancel(&heartbeat_timer_);
  }

  void OnOnline() {
    PrintDebugInfo();

    Test_->latest_code_.clear();

    for (auto listener : Test_->online_listeners_)
      if (auto locked_listener = listener.lock()) locked_listener->OnOnline();

    SendCachedTransactions();
  }

  void OnOffline(std::error_code code) {
    Test_->latest_code_ = code;

    for (auto listener : Test_->online_listeners_)
      if (auto locked_listener = listener.lock())
        locked_listener->OnOffline(code);
  }

  void OnShutdown() {
    for (auto listener : Test_->online_listeners_)
      if (auto locked_listener = listener.lock()) locked_listener->OnShutdown();
  }

  void OnBackward(std::error_code code) { Test_->latest_code_ = code; }

  void SendCachedTransactions() {
    if (Test_->connection_) {
      KwaiLogger::Info("Test send transactions.");
      for (auto transaction : Test_->transactions_)
        Test_->connection_->SendMessage(transaction.second);
      Test_->transactions_.clear();

    } else if (!Test_->transactions_.empty()) {
      KwaiLogger::Warn("Test not online, schedule to check timeout.");
      Test_->ScheduleToCheckTimeout();
    }
  }

  void FailAllCachedTransaction() {
    decltype(Test_->transactions_) transactions =
        std::move(Test_->transactions_);
    for (auto transaction : transactions) {
      transaction.second->SetErrorCode(TestError::kShutdown);
      transaction.second->Complete();
    }
  }

  template <class State, class Event>
  void OnNoTransition(const State&, const Event&) {
    KwaiLogger::Warn("No transition from {} with {}",
                     boost::sml::aux::get_type_name<State>(),
                     boost::sml::aux::get_type_name<Event>());
    // TODO(Lynn) Record this to debug
  }

  void PrintDebugInfo() {
    auto current_access_point = Test_->CurrentAccessPoint();
    auto server_time =
        std::chrono::system_clock::to_time_t(Test_->GetServerClock()->Now());

    // FIXME(Lynn)
    std::ostringstream oss;
    oss << std::put_time(localtime(&server_time), "%Y-%m-%d %H:%M:%S");
    KwaiLogger::Info(
        "Test version is {}, AppId is {}, UserId is {}, InstanceId is {}, "
        "Current Access Point is {}:{}, server time is {}",
        Version(), Test_->GetAppId(), Test_->GetUserId(),
        Test_->GetInstanceId(), current_access_point.first,
        current_access_point.second, oss.str());
  }

  Test* Test_;
  util::Queue::TaskHandle heartbeat_timer_;
};

enum ITest::State Test::State() const {
  if (!SM) return ITest::kInit;

  // clang-format off
  if (SM->is("Power Off"_s))          return ITest::kInit;
  else if (SM->is("Connecting"_s))    return ITest::kConnecting;
  else if (SM->is("Connected"_s))     return ITest::kConnected;
  else if (SM->is("Registering"_s))   return ITest::kRegistering;
  else if (SM->is("Unregistering"_s)) return ITest::kUnregistering;
  else if (SM->is("Online"_s))        return ITest::kOnline;
  else                                return ITest::kInit;
  // clang-format on
}


