#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <memory>
#include "asio.hpp"
#include "connection.h"


namespace http{
namespace client
{
class client{
public:
    client(const client&) = delete;
    client& operator=(const client&) = delete;
    client(const std::string& host, const std::string& port);
    void start();
    void stop();
    void run();
private:
    void do_connect();
    void do_exception_wait();
    asio::io_context io_context_;
    std::shared_ptr<connection> connection_;
    asio::signal_set signal_set_;
};

} // namespace client
} // namespace http

#endif