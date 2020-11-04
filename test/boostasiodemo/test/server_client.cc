#define ASIO_STANDALONE
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS
#define ASIO_HAS_STD_ATOMIC

#include "asio.hpp"

#include <iostream>
#include <string>
#include <thread>

void server(){
    typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 2001);
    asio::ip::tcp::acceptor acc(service, ep);
    socket_ptr sock(new asio::ip::tcp::socket(service));
    acc.accept(*sock);
    while(true){
        char data[512];
        size_t len = sock->read_some(asio::buffer(data));
        
        if(len > 0){
            std::cout<<"server receive: "<<data<<std::endl;
            asio::write(*sock, asio::buffer("ok", 2));
        }
    }
}

void client(){
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 2001);
    asio::ip::tcp::socket sock(service);
    sock.open(asio::ip::tcp::v4());
    sock.connect(ep);
    sock.write_some(asio::buffer("GET /index.html\r\n"));

    char buff[1024];
    sock.read_some(asio::buffer(buff, 1024));
    std::cout<<"client receive: "<<buff<<std::endl;
    sock.shutdown(asio::ip::tcp::socket::shutdown_receive);
    sock.close();
}

int main(int argc, char* argv[]) {
    std::thread server_thread(&server);
    std::thread client_thread(&client);
    if(client_thread.joinable())client_thread.join();
    if(server_thread.joinable())server_thread.join();

    asio::io_service service;
    asio::ip::tcp::resolver resolver(service);
    asio::ip::tcp::resolver::query query("www.yahoo.com", "80");
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    asio::ip::tcp::endpoint ep = *iter;
    std::cout<< "ip is: " << ep.address().to_string()  << std::endl;
    return 0;
}