
#include "asio.hpp"

#include <iostream>
#include <thread>

asio::io_service g_service;

class client{
public:
    client(std::string ip, int port): socket_(g_service), ep_(asio::ip::address::from_string(ip), port){}

    void send(){
        while(true){
            socket_.send("client data to server");
        }
    }

    void start(){
        socket_.connect(ep_);
        char buff[1024];
        while(true){
            socket_.read_some(asio::buffer(buff));
            std::cout<<"client receive: "<<buff<<std::endl;
        }
    }

private:
    asio::ip::tcp::endpoint ep_;
    asio::ip::tcp::socket socket_;

};

void do_start(client& cli){
    cli.start();
}

void do_upload(client& cli){
    cli.send();
}


int main(){

    client cli("127.0.0.1", 4001);
    std::thread cli_thread(&do_start, cli);
    std::thread up_thread(&do_upload, cli);

    up_thread.join();
    cli_thread.join();
    return 0;
}






