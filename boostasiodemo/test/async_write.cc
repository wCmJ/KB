#include "asio.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <exception>

// 相当于我们理解的session, 建立一个会话
struct Session {
    std::shared_ptr<asio::ip::tcp::socket> sock;
    std::string buf;
    std::size_t total_bytes_written;
};

// 回调函数, 为了保证数据全部传输完毕
void callback(const asio::error_code &ec,
              std::size_t bytes_transferred,
              std::shared_ptr<Session> s) {
    if (ec.value() != 0) {
        std::cout << "Error occurred! Error code = "
                  << ec.value()
                  << ". Message: " << ec.message();
        s->sock->close();
        return;
    }
    std::cout<<"callback enter"<<std::endl;
    sleep(2);
    ///*
    s->total_bytes_written += bytes_transferred;
    if (s->total_bytes_written == s->buf.length()) {
        std::cout<<"callback exit. no recursive"<<std::endl;
        s->sock->close();
        return;  // 数据全部写完, 没有必要继续
    }
    //*/

    /*
    s->sock->async_write_some(  // 继续向下执行回调, 递归形式的迭代
            asio::buffer(  // 截取有效数据段
                    s->buf.c_str() + s->total_bytes_written,
                    s->buf.length() - s->total_bytes_written),
            std::bind(callback, 
                      std::placeholders::_1,  // 错误码
                      std::placeholders::_2,  // 写入的数据数
                      s)
    );*/
    s->sock->async_write_some(  // 启动异步读写
            asio::buffer(s->buf),
            std::bind(callback, std::placeholders::_1, std::placeholders::_2, s)
    );
}


void writeToSocket(std::shared_ptr<asio::ip::tcp::socket> sock) {
	// 分配到堆空间的, 为了保证数据传输完成前都存在
    std::shared_ptr<Session> s(new Session);  

    s->buf = std::string("Hello world!");
    s->total_bytes_written = 0;
    s->sock = std::move(sock);

    s->sock->async_write_some(  // 启动异步读写
            asio::buffer(s->buf),
            std::bind(callback, std::placeholders::_1, std::placeholders::_2, s)
    );
}

void server(){
    typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 19999);
    asio::ip::tcp::acceptor acc(service, ep);
    socket_ptr sock(new asio::ip::tcp::socket(service));
    acc.accept(*sock);
    int cnt = 1;
    while(true){
        try{
            char data[512];
            size_t len = sock->read_some(asio::buffer(data));
            
            if(len > 0){
                std::cout<<"server receive: "<<data<<std::endl;
                //asio::write(*sock, asio::buffer("ok", 2));
            }
        }
        catch(std::exception &e){
            if(++cnt % 10000 == 0){
                std::cout<<e.what()<<std::endl;
            }
        }
    }

}

void server1(){
    typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 19999);
    asio::ip::tcp::acceptor acc(service, ep);
    socket_ptr sock(new asio::ip::tcp::socket(service));
    acc.accept(*sock);
    while(true){
        std::cout<<"server receive: "<<std::endl;
        char data[512];
        size_t len = sock->read_some(asio::buffer(data));
        std::cout<<"server read_some end"<<std::endl;
        if(len > 0){
            std::cout<<"server receive: "<<data<<std::endl;
            asio::write(*sock, asio::buffer("ok", 2));
        }
    }
}


int main() {

    std::thread server_thread(server1);

    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 19999;
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
        //writeToSocket(sock);
        ioc.run();  // 启动异步调用
    } catch (asio::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
        return e.code().value();
    }
    server_thread.join();
    return 0;
}