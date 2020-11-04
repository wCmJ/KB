
#include "asio.hpp"

#include <future>
#include <chrono>
#include <string>
#include <iostream>
#include <thread>

using namespace std;

static std::string taskid_;
static int log_fd;
static char receive_buff[50];
static asio::io_context io_context_;

//static asio::ip::tcp::socket socket_;

void run(asio::io_service& io_context_, asio::ip::tcp::socket& socket_, asio::chrono::steady_clock::duration timeout)
  {
    // Restart the io_context, as it may have been left in the "stopped" state
    // by a previous operation.
    std::cout<<"1------"<<endl;
    io_context_.restart();

    // Block until the asynchronous operation has completed, or timed out. If
    // the pending asynchronous operation is a composed operation, the deadline
    // applies to the entire operation, rather than individual operations on
    // the socket.
    std::cout<<"2------"<<endl;
    io_context_.run_for(timeout);

    // If the asynchronous operation completed successfully then the io_context
    // would have been stopped due to running out of work. If it was not
    // stopped, then the io_context::run_for call must have timed out.
    if (!io_context_.stopped())
    {
      // Close the socket to cancel the outstanding asynchronous operation.
      std::cout<<"3------"<<endl;
      socket_.close();

      // Run the io_context again until the operation completes.
      io_context_.run();
    }
  }

int receive_from_client(asio::ip::tcp::socket& socket_){

     
    //while(!res) {
        //std::cout<<"receive_from_client. res is 0"<<". socket info: " << socket_.remote_endpoint().address() <<  ". " << socket_.remote_endpoint().port() <<std::endl;
    size_t res = socket_.read_some(asio::buffer(receive_buff));
    //}
    return res;
}

void print_time(){
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);

  // 输出时间
    std::cout << ctime(&tt) << std::endl;

    for(int i = 0;i<sizeof(receive_buff);++i){
        std::cout<<receive_buff[i];
    }
    cout<<endl;
    memset(receive_buff, 0, sizeof(receive_buff));
}

int receive(asio::ip::tcp::socket& socket_){
    taskid_.clear();
    try{
        if(0)
        {
            int len = socket_.read_some(asio::buffer(receive_buff));
            std::cout<<"receive data: "<<receive_buff<< std::endl;
            sleep(1);
        }
        else{
            if(1){                
                std::cout<<"---------------receive ENTER. ";
                print_time();
                size_t len = 0;
                auto status = std::async(std::launch::async, [&] (){             
                        //len = asio::read(socket_, asio::buffer(receive_buff, sizeof(receive_buff)));// block read
                        len = socket_.read_some(asio::buffer(receive_buff));
                    });
                auto res = status.wait_for(std::chrono::seconds{ 1 });
                switch (res)
                {
                case std::future_status::deferred:
                    //... should never happen with std::launch::async
                    std::cout<<"std::future_status::deferred"<<std::endl;
                    break;
                case std::future_status::ready:
                    //parse data and get taskid
                    std::cout<<"std::future_status::ready"<<std::endl;
                    if(len > 0){
                        for(int i = 0;i<len;++i){
                            std::cout<<receive_buff[i];
                        }
                        std::cout<<std::endl;
                    }
                    break;
                case std::future_status::timeout:
                    //...
                    std::cout<<"std::future_status::timeout"<<std::endl;
                    break;
                }

            }
            else 
            {
                size_t len = 0;
                std::cout<<"server receive. "<< "socket info: " << socket_.remote_endpoint().address() <<  ". " << socket_.remote_endpoint().port() <<std::endl;
                std::string err1 = "receive: std::future_status::deferred\n";
                std::string err2 = "receive: std::future_status::ready\n";
                std::future<int> status = std::async(std::launch::async, receive_from_client, std::ref(socket_));
                //std::string FileData = status.get();
                std::chrono::milliseconds span(30);
                //int cnt = 1;
                //while (status.wait_for(span) != std::future_status::ready)
                //    std::cout << cnt++ << " ";
                //std::cout << std::endl;
                len = status.get();
                std::cout<<"receive data: "<<len<<std::endl;
                write(log_fd, receive_buff, len);
                sleep(1);
                }
                /*
                switch (status)
                    {
                    case std::future_status::deferred:
                        //... should never happen with std::launch::async
                        std::cout<<"receive: std::future_status::deferred\n"<<std::endl;
                        write(log_fd, err1.c_str(), err1.size());
                        break;
                    case std::future_status::ready:
                        std::cout<<"receive: std::future_status::ready"<< ". len is: " << len << std::endl;
                        //parse data and get taskid
                        if(len > 0){
                            write(log_fd, buff, len);
                            std::cout<<buff<<std::endl;
                            return len;
                        }
                        break;
                    case std::future_status::timeout:
                        std::cout<<"receive: std::future_status::timeout"<<std::endl;
                        write(log_fd, err2.c_str(), err2.size());                
                        //...
                        break;
                    }*/ 
            }
    }
    catch(...){
        //log
        std::cout<<"receive: exceptioin"<<std::endl;
    }
    std::cout<<"---------------receive exit. ";
    print_time();
    return -1;
}


void client_thread(){
    /*
    asio::ip::tcp::socket socket_(io_context_);
    asio::ip::tcp::resolver::results_type endpoints =
      asio::ip::tcp::resolver(io_context_).resolve("127.0.0.1", "30001");
    asio::error_code ec;
    asio::connect(socket_, endpoints);
   //asio::async_connect(socket_, endpoints, );
    */
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 40001);
    asio::ip::tcp::socket sock(service);
    sock.open(asio::ip::tcp::v4());
    sock.connect(ep);
    //sleep(2);
    int i = 5;
    while(i--){
        std::cout<<"client ready to send."<<std::endl;
        sock.write_some(asio::buffer("0123456789"));
        sleep(5);
    }

    char buff[1024];
    sock.read_some(asio::buffer(buff, 1024));
    std::cout<<"client receive: "<<buff<<std::endl;
    sock.shutdown(asio::ip::tcp::socket::shutdown_receive);
    sock.close();
}

void server_thread(){
    typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 40001);
    asio::ip::tcp::acceptor acc(service, ep);
    socket_ptr sock(new asio::ip::tcp::socket(service));
    acc.accept(*sock);
    //asio::ip::tcp::socket::non_blocking_io io_option(true);
    //sock->io_control(io_option);
    //sock->non_blocking(true);
    char buff[1024];
    int len = 0;
    while(true){
        std::cout<<"START: server ready to receive: "<<std::endl;
        if(0)
        {
            
            //sock->read_some(asio::buffer(buff));
            len = sock->read_some(asio::buffer(buff));
            //asio::async_read(*sock, asio::buffer(receive_buff), std::bind(print_time));
            //len += asio::read(*sock, asio::buffer(buff, 40));
            std::cout<<"END: server_thread receive: "<< std::endl;
            for(int i = 0;i<len;++i){
                std::cout<<buff[i];
            }
            std::cout<<std::endl;
            memset(buff, 0, sizeof(buff));

        }
        else{
            
            //std::cout<<"server to read. ";print_time();
            //asio::async_read(*sock, asio::buffer(receive_buff),std::bind(print_time));
            //sock->async_receive(asio::buffer(receive_buff),std::bind(print_time));
            //asio::async_receive(*sock, asio::buffer(receive_buff), std::bind(print_time));
            
            //service.restart();
            //service.run_for(std::chrono::seconds(1));
            
            int len = sock->read_some(asio::buffer(buff));
            if(len > 0){
                for(int i = 0;i<len;++i){
                    std::cout<<buff[i];
                }
                std::cout<<std::endl;
                memset(buff, 0, sizeof(buff));
            }
            //asio::async_read(*sock, asio::buffer(receive_buff), std::bind(print_time));
            //run(service, *sock, std::chrono::seconds(3));
            //service.run_for(std::chrono::seconds(3));
            //std::cout<<"server to read EXIT";print_time();
        }
        //receive(*sock);
        std::cout<<"END: server_thread receive: "<< std::endl;
    }

}

int test_async(){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 99;
}
std::string fun_2() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    write(log_fd, "abcd", 4);
    return "hello";
}

int main(){
    log_fd = open("./log_file.log", O_CREAT | O_WRONLY);
    if(log_fd == -1){
        std::cout<<"open log file error"<<std::endl;

    }
    else{
        std::cout<<"open log file success"<<std::endl;
    }

if(0){
    {
        auto x = async(std::launch::async, fun_2);
        cout << "456  ";
        print_time();
        if  (x.wait_for(chrono::seconds(1)) == future_status::timeout){
            cout << "time out. ";
            print_time();
        }        
        else
            cout << x.get();
    }
}


    while(1){
        auto status = std::async(test_async);
        auto res = status.wait_for(std::chrono::seconds(1));
        if (res == std::future_status::deferred) {
            std::cout << "deferred. ";
            print_time();
        } else if (res == std::future_status::timeout) {
            std::cout << "timeout. ";
            print_time();
        } else if (res == std::future_status::ready) {
            std::cout << "ready! ";
            print_time();
        }

    }

        



    
    std::thread ser_th(&server_thread);
    std::thread cli_th(&client_thread);


    cli_th.join();
    ser_th.join();
    std::cout<<"thread terminate"<<std::endl;
    close(log_fd);

    return 0;
}

