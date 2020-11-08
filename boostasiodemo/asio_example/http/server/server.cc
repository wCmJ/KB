
#include "server.h"

namespace http{
namespace server{
server::server( const std::string& address,
    const std::string& port)
  :	io_context_(2),
	  signal_set_(io_context_),
	  acceptor_(io_context_)
	{

    signal_set_.add(SIGINT);
    signal_set_.add(SIGTERM);

    do_wait();


		asio::ip::tcp::resolver resovler(io_context_);
		asio::ip::tcp::endpoint endpoint = *resovler.resolve(address, port).begin();
		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(endpoint);
		acceptor_.listen();

		do_accept();
	}

void server::run(){
  std::cout<<"run begin"<<std::endl;
  io_context_.run();
  std::cout<<"run end"<<std::endl;
}  

void server::do_wait(){
  signal_set_.async_wait(
    [this](std::error_code, int){
        acceptor_.close();

      }
    );
}


void server::do_accept(){

	acceptor_.async_accept(
		[this](std::error_code ec, asio::ip::tcp::socket socket){
			if(!acceptor_.is_open()){
				return;
			}
			if(!ec){
				//store socket
        std::cout<<"accept connect: "<<socket.remote_endpoint().address()<< "  "<<socket.remote_endpoint().port()<<std::endl;
        connection_manager_.start(std::make_shared<connection>(std::move(socket), connection_manager_));
			}
			do_accept();
		}
	);
}
}
}

