
#ifndef SERVER_H_
#define SERVER_H_



#include "asio.hpp"
#include <iostream>
#include <string>
#include "connection_manager.h"


namespace http{
namespace server{
class server{
public:
    server(const server&) = delete;
    server& operator=(const server&) = delete;
    explicit server(const std::string& address, const std::string& port);

    void run();

private:

    void do_accept();
    void do_wait();


    asio::io_context io_context_;
    
    asio::ip::tcp::acceptor acceptor_;

    asio::signal_set signal_set_;

    connection_manager connection_manager_;

};
}
}

#endif