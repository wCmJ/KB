
#include "asio.hpp"

#include <iostream>
#include <thread>

asio::io_service g_service;



int main(){
    asio::ip::tcp::acceptor acceptor(g_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(),8001));
    while(true){
        asio::ip::tcp::socket sock(g_service);
        acceptor.accept(sock);
        char buff[1024];
        int bytes = asio::read(sock, asio::buffer(buff));
        


    }



    return 0;
}



