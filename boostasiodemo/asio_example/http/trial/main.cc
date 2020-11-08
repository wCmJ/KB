
#include "asio.hpp"

#include <iostream>
#include <string>
#include <thread>

static const std::string ip = "127.0.0.1";
static const std::string port = "50002"; 


static void client_do_write(asio::ip::tcp::socket client_socket){
    std::cout<<"client_do_write thread: "<<std::this_thread::get_id()<<std::endl;
    if(0)
    {
        static int cnt = 1;
        client_socket.write_some(asio::buffer("hello server " + std::to_string(cnt++)));
        sleep(2);
        client_do_write(std::move(client_socket));
    }




    client_socket.async_write_some(
        asio::buffer("Hello Server"),
        [&client_socket](std::error_code ec, std::size_t bytes){
            if(!ec){
                sleep(1);
                client_do_write(std::move(client_socket));
            }
        }
    );
    std::cout<<"client_do_write thread: "<<std::this_thread::get_id()<<" end."<<std::endl;
}

static void client(asio::io_context& io_context_){
    asio::ip::tcp::socket client_socket(io_context_);
    asio::ip::tcp::resolver resolver_(io_context_);
    asio::ip::tcp::endpoint ep = *resolver_.resolve(ip, port).begin();
    try{
        client_socket.connect(ep);
    }
    catch(std::exception e){
        std::cout<<"connect exception: "<<e.what()<<std::endl;
    }
    std::cout<<"client thread: "<<std::this_thread::get_id()<<" . connect success."<<std::endl;
    client_do_write(std::move(client_socket));
}

static void server_do_read(asio::ip::tcp::socket client_socket){
    char buffer[128];
    std::cout<<"server_do_read thread: "<<std::this_thread::get_id()<<std::endl;
    if(0)
    {
        auto len = client_socket.read_some(asio::buffer(buffer, sizeof(buffer)));
        for(int i = 0;i<len;++i){
            std::cout << buffer[i];
        }
        std::cout<<std::endl;
        server_do_read(std::move(client_socket));
    }


    client_socket.async_read_some(
        asio::buffer(buffer, sizeof(buffer)),
        [&client_socket, buffer](asio::error_code ec, std::size_t bytes){
            
            if(!ec){
                for(int i = 0;i<bytes;++i){
                    std::cout<<buffer[i];
                }
                std::cout<<std::endl;
                server_do_read(std::move(client_socket));
            }
        }
    );
    std::cout<<"server_do_read thread: "<<std::this_thread::get_id()<<" end."<<std::endl;
}

static void server(asio::io_context& io_context_){
    //asio::ip::tcp::socket server_socket(io_context_);
    asio::ip::tcp::resolver resolver_(io_context_);
    asio::ip::tcp::endpoint ep = *resolver_.resolve(ip, port).begin();
    asio::ip::tcp::acceptor acceptor_(io_context_);
    acceptor_.open(ep.protocol());
    acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(ep);
    acceptor_.listen();
    std::error_code ec;
    asio::ip::tcp::socket client_socket = acceptor_.accept(ec);
    if(ec){
        std::cout<<"accept failed"<<std::endl;
        return;
    }
    std::cout<<"server thread: "<<std::this_thread::get_id()<<" ,accept success."<<std::endl;
    //while(true){
        server_do_read(std::move(client_socket));
    //}
}



int main(){
    asio::io_service io_service_;
    asio::deadline_timer timer();
    


    return 0;    
}


