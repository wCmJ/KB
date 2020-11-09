#include "asio.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_set>

static const std::string ip = "127.0.0.1";
static const std::string port = "50002"; 


class server{
public:
    server(const server&) = delete;
    server& operator=(const server&) = delete;
    server(const std::string& ip, const std::string &port):
        io_context_(1),
        acceptor_(io_context_),
        socket_(io_context_){
            asio::ip::tcp::resolver resolver_(io_context_);
            asio::ip::tcp::endpoint ep = *resolver_.resolve(ip, port).begin();
            acceptor_.open(ep.protocol());
            acceptor_.bind(ep);
            acceptor_.listen();
            do_accept();

        }

    void run(){
        io_context_.run();
    }


    void do_accept()
    {
        std::cout<<"do_accept: "<<std::this_thread::get_id()<<std::endl;
        acceptor_.async_accept(
            [this](std::error_code ec, asio::ip::tcp::socket socket)
            {
                // Check whether the server was stopped by a signal before this
                // completion handler had a chance to run.
                if (!acceptor_.is_open())
                {
                return;
                }

                if (!ec)
                {
                    std::cout<<"do_read: "<<socket.remote_endpoint().address()<<" , "<<socket.remote_endpoint().port()<<" ";
                    socket_ = std::move(socket);
                    do_read();                
                }
                do_accept();
            });
    }

    void do_read(){
        std::cout<<"do_read: "<<std::this_thread::get_id()<<std::endl;
        socket_.async_read_some(
            asio::buffer(buf, sizeof(buf)),
            [this](std::error_code ec, std::size_t bytes){
                if(!ec){
                    std::cout<<"buf: "<<std::this_thread::get_id()<<" .bytes: "<<bytes<<std::endl;
                    for(int i = 0;i<bytes;++i){
                        std::cout<<buf[i];
                    }
                    socket_.write_some(asio::buffer("I'm server."));
                    std::cout<<std::endl;
                }
                else{
                    std::cout<<"ec is true"<<std::endl;
                }
                do_read();
            }
        );
    }


private:
    asio::io_context io_context_;
    asio::ip::tcp::acceptor acceptor_;
    asio::ip::tcp::socket socket_;
    char buf[128];
    std::unordered_set<std::shared_ptr<asio::ip::tcp::socket>> sockets_;
};



static void server_do_read(asio::ip::tcp::socket& client_socket){
    static char buffer[128];
    std::cout<<"server_do_read thread: "<<std::this_thread::get_id()<<std::endl;
    /*
    if(0)
    {
        auto len = client_socket.read_some(asio::buffer(buffer, sizeof(buffer)));
        for(int i = 0;i<len;++i){
            std::cout << buffer[i];
        }
        std::cout<<std::endl;
        server_do_read(std::move(client_socket));
    }
    */

    client_socket.async_read_some(
        asio::buffer(buffer, sizeof(buffer)),
        [&client_socket](asio::error_code ec, std::size_t bytes){
            std::cout<<"server read some"<<std::endl;
            if(!ec){
                for(int i = 0;i<bytes;++i){
                    std::cout<<buffer[i];
                }
                std::cout<<std::endl;
                server_do_read(client_socket);
            }
        }
    );
    std::cout<<"server_do_read thread: "<<std::this_thread::get_id()<<" end."<<std::endl;
}

static void server_func(asio::io_context& io_context_){
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
        server_do_read(client_socket);
    //}
}




int main(){

    {
        server ser(ip, port);
        ser.run();
        return 0;

    }



    asio::io_context io_context_;
   //std::thread th_server(server_func, std::ref(io_context_));
    server_func(io_context_);
    std::cout<<"main ready to run"<<std::endl;
    io_context_.run();
    //th_server.join();
    return 0;
}

