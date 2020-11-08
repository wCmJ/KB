#include "client.h"


namespace http{
namespace client
{

client::client(const std::string& host, const std::string& port)
:   io_context_(2),signal_set_(io_context_)
{
    asio::ip::tcp::socket socket(io_context_);
    asio::ip::tcp::resolver resolver(io_context_);
    asio::ip::tcp::endpoint ep = *resolver.resolve(host, port).begin();
    
    do_exception_wait();
    std::cout<<"ready to connect"<<std::endl;
    socket.async_connect(ep,
        [this, &socket](std::error_code ec){
            if(!ec){
                std::cout<<"connection success"<<std::endl;
                connection_ = std::make_shared<connection>(std::move(socket));
            }
        }
    );
}

void client::do_connect(){

}


void client::run(){
    std::cout<<"run begin"<<std::endl;
    io_context_.run();
    std::cout<<"run end"<<std::endl;
}

/*
void client::start(){
    connection_->start();
}

void client::stop(){

    connection_->stop();
}
*/
void client::do_exception_wait(){
    signal_set_.async_wait(
      [this](std::error_code /*ec*/, int /*signo*/)
      {
        // The server is stopped by cancelling all outstanding asynchronous
        // operations. Once all operations have finished the io_context::run()
        // call will exit.
        
      });
}

} // namespace client
} // namespace http

