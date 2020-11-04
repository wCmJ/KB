#include "asio.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>

std::mutex g_mutex;
std::condition_variable g_cv;


struct Session {
    std::shared_ptr<asio::ip::tcp::socket> sock;
    std::unique_ptr<char[]> buf;
    std::size_t total_bytes_read;
    unsigned int buf_size;
};

void callback(const asio::error_code &ec,
              std::size_t byte_transferrd,
              std::shared_ptr<Session> s) {
    try{
        if (ec.value() != 0) {
            std::cout << "Error occured! Error code = "
                    << ec.value()
                    << ". Message: " << ec.message();
            return;
        }
        std::cout<<"callback receive data len : "<< byte_transferrd<<std::endl;
        s->total_bytes_read += byte_transferrd;
        for(int i = 0;i<s->total_bytes_read;++i){
            std::cout<<s->buf[i];
        }
        std::cout<<std::endl;

        s->sock->async_read_some(
                asio::buffer(s->buf.get() + s->total_bytes_read,
                                    s->buf_size - s->total_bytes_read),
                std::bind(callback,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        s)
        );
    }catch (asio::system_error &e) {
        std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
    }
}

void readFromSocket(std::shared_ptr<asio::ip::tcp::socket> sock) {
    try{
        std::shared_ptr<Session> s(new Session);
        const unsigned int MESSAGE_SIZE = 50;

        s->buf.reset(new char[MESSAGE_SIZE]);
        s->total_bytes_read = 0;
        s->sock = std::move(sock);
        s->buf_size = MESSAGE_SIZE;

        s->sock->async_read_some(
                asio::buffer(s->buf.get(),
                                    s->buf_size),
                std::bind(callback,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        s)
        );
        std::cout<<"readFromSocket receive. data len : "<< s->total_bytes_read << std::endl;
        for(int i = 0;i<s->buf_size;++i){
            std::cout<<s->buf[i];
        }
        std::cout<<std::endl;
    }catch (asio::system_error &e) {
        std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
    }



}


void client(){
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 49999;
    try {
        asio::ip::tcp::endpoint ep(
                asio::ip::address::from_string(raw_ip_address),
                port_num
        );
        asio::io_context ioc;

        std::shared_ptr<asio::ip::tcp::socket> sock(
                new asio::ip::tcp::socket(ioc, ep.protocol())
        );

        sock->connect(ep);
        readFromSocket(sock);

        std::thread t([&ioc]() {ioc.run(); });
        
        std::unique_lock<std::mutex> lc(g_mutex);
        g_cv.wait(lc);
        ioc.stop();
        t.join();
        sock->close();
        std::cout<<"wait finish"<<std::endl;
    } catch (asio::system_error &e) {
        std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
    }
    std::cout<<"---------------client thread exit"<<std::endl;
}

void server(){
    typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 49999);
    asio::ip::tcp::acceptor acc(service, ep);
    socket_ptr sock(new asio::ip::tcp::socket(service));
    acc.accept(*sock);
    while(true){
        try{
            std::string info = "hello client";
            
            if(sock->is_open())
                asio::write(*sock, asio::buffer(info, info.size()));
            std::cout<<"server write : "<< info << std::endl;
            sleep(4);
        }
        catch (asio::system_error &e) {
        std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
        sock->close();
        break;
    }
        /*
        std::cout<<"server receive: "<<std::endl;
        char data[512];
        size_t len = sock->read_some(asio::buffer(data));
        std::cout<<"server read_some end"<<std::endl;
        if(len > 0){
            std::cout<<"server receive: "<<data<<std::endl;
            asio::write(*sock, asio::buffer("ok", 2));
        }
        */
    }
    std::cout<<"server thread end"<<std::endl;
}


int main() {
    std::thread server_thread(&server);
    std::thread client_thread(&client);
    sleep(5);
    std::cout<<"main notify client to exit"<<std::endl;
    g_cv.notify_all();
    client_thread.join();
    std::cout<<"---------------main: client thread end"<<std::endl;
    server_thread.join();
    
    std::cout<<"---------------main: server thread end"<<std::endl;
}