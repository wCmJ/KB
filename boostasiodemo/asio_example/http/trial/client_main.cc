#include "asio.hpp"

#include <iostream>
#include <string>
#include <thread>

static const std::string ip = "127.0.0.1";
static const std::string port = "50002"; 


class client: public std::enable_shared_from_this<client>{
public:
    client(const client&) = delete;
    client& operator=(const client&) = delete;
    client(const std::string& ip, const std::string& port)
    :   io_context_(1),
        socket_(io_context_)
    {
        asio::ip::tcp::resolver resolver_(io_context_);
        asio::ip::tcp::endpoint ep = *resolver_.resolve(ip, port).begin();
        try{
            socket_.connect(ep);
        }
        catch(...){

        }
        do_write();
    }

    void do_write(){
        std::cout<<"do_write: "<<std::this_thread::get_id()<<std::endl;
        socket_.async_write_some(
            asio::buffer("Hello Server"),
            [this](std::error_code ec, std::size_t bytes){
                if(!ec){
                    std::cout<<"ec is false. do_write: "<<bytes<<std::endl;                            
                }
                else{
                    std::cout<<"ec is true. do_write: "<<bytes<<std::endl;
                }
                do_read();
                sleep(1);
                do_write();
            }
        );
    }

    void do_read(){
        //std::cout<<"do_read: "<<std::this_thread::get_id()<<std::endl;
        socket_.async_read_some(
            asio::buffer(buf, sizeof(buf)),
            [this](std::error_code ec, std::size_t bytes){
                if(!ec){
                    std::cout<<"do_read ec is false: "<<std::this_thread::get_id()<<" :";
                    for(int i = 0;i<bytes;++i){
                        std::cout<<buf[i];
                    }
                    std::cout<<std::endl;
                }
                else{
                    std::cout<<"do_read ec is true"<<std::endl;
                }
            }
        );
    }

    void run(){
        io_context_.run();
    }


private:
    asio::io_context io_context_;
    asio::ip::tcp::socket socket_;
    char buf[128];
};


static void client_do_write(asio::ip::tcp::socket& client_socket){
    std::cout<<"client_do_write thread: "<<std::this_thread::get_id()<<std::endl;
    /*
    if(0)
    {
        static int cnt = 1;
        client_socket.write_some(asio::buffer("hello server " + std::to_string(cnt++)));
        sleep(2);
        client_do_write(std::move(client_socket));
    }
    */



    client_socket.async_write_some(
        asio::buffer("Hello Server"),
        [&client_socket](std::error_code ec, std::size_t bytes){
            if(!ec){
                //sleep(1);
                client_do_write(client_socket);
            }
        }
    );
    std::cout<<"client_do_write thread: "<<std::this_thread::get_id()<<" end."<<std::endl;
}

static void client_func(asio::io_context& io_context_){
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
    //client_do_write(std::move(client_socket));
    client_do_write(client_socket);
}




int main(){

    {
        client cli(ip, port);
        cli.run();
        return 0;
    }


    asio::io_context io_context_;
    //std::thread th_client(client_func, std::ref(io_context_));
    client_func(io_context_);
    io_context_.run();
    //th_client.join();
    return 0;
}