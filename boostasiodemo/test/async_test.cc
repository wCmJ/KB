#include "asio.hpp"

#include <iostream>
#include <thread>


class client{
public:
    client(asio::io_service& service): socket_(service), ep_(asio::ip::address::from_string("127.0.0.1"), 2001){

    }
    void do_connect(){
        socket_.connect(ep_);
    }
    void do_read(){
        char buff[1024];
        socket_.read_some(asio::buffer(buff));
        std::cout<<"client read: "<<buff<<std::endl;
        sleep(1000);
        socket_.send(asio::buffer(buff));
    }
private:
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::endpoint ep_;
};



//void completion_handler(const boost::system::error_code& ec){
void completion_handler(const asio::error_code& ec){

    std::cout<<"completion_handler"<<std::endl;
    while(true){
        char buff[2048];
        //asio::read();
    }
}


void server_thread(){
    std::cout<<"Start: server thread"<<std::endl;
    asio::io_service service;
    asio::ip::tcp::acceptor acceptor(service, asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 2001));
    asio::ip::tcp::socket sock(service);
    acceptor.accept(sock);
    while(true){
        sock.send("info from server\n");
        char buff[1024];
        sock.receive(asio::buffer(buff));
    }
}

void client_thread(client& cli){
    //tcp_socket.async_connect(ep, completion_handler);
    //service.run();
}


int main(){
    asio::io_service service;
    client cli_(service);
    std::thread cli_thread(client_thread, cli_);
    std::cout<<"end service.run"<<std::endl;
    return 0;
}


