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


void server_do_receive(std::shared_ptr<asio::ip::tcp::socket> socket, char* buffer_, int len){
    socket->async_read_some(
        asio::buffer(buffer_, len),
        [socket, buffer_, len](std::error_code ec, std::size_t bytes_receive){
            if(!ec){
                std::cout<<"server receive data len: "<<bytes_receive<<std::endl;
                for(int i = 0;i<bytes_receive;++i){
                    std::cout<<buffer_[i];
                }
                server_do_receive(socket, buffer_, len);
            }
            else{
                socket->close();
            }
        }
    );
}



void server(){
    typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 29999);
    asio::ip::tcp::acceptor acc(service, ep);
    socket_ptr sock(new asio::ip::tcp::socket(service));
    acc.accept(*sock);
    while(true){
        {
            char data[512];        
            server_do_receive(sock, data, sizeof(data));
        }
    }
}






void client(){
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 29999);
    asio::ip::tcp::socket sock(service);
    sock.open(asio::ip::tcp::v4());
    sock.connect(ep);
    //sock.write_some(asio::buffer("GET /index.html\r\n"));
    int cnt = 10;
    while(cnt--){
        char *buff = "message from client";
        std::cout<<"client receive: "<<std::endl;
        sock.send(asio::buffer(buff, sizeof(buff)));
        sleep(2);        
    }
    sock.shutdown(asio::ip::tcp::socket::shutdown_receive);
    sock.close();
}

void client1(){
    try{
        asio::ip::tcp::endpoint ep(
                asio::ip::address::from_string("127.0.0.1"),
                29999
        );

        asio::io_context ioc;

        std::shared_ptr<asio::ip::tcp::socket> sock(
                new asio::ip::tcp::socket(ioc, ep.protocol())
        );

        sock->connect(ep);
        //writeToSocket(sock);
        ioc.run();  // 启动异步调用  
        std::cout<<"client1 run end"<<std::endl;   
    } 
    catch (asio::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
    }
}


int main(int argc, char* argv[]) {
    std::thread server_thread(&server);
    std::thread client_thread(&client1);
    if(client_thread.joinable())client_thread.join();
    if(server_thread.joinable())server_thread.join();

    asio::io_service service;
    asio::ip::tcp::resolver resolver(service);
    asio::ip::tcp::resolver::query query("www.o.com", "80");
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    asio::ip::tcp::endpoint ep = *iter;
    std::cout<< "ip is: " << ep.address().to_string()  << std::endl;
    return 0;
}