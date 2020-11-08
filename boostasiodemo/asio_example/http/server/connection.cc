#include "connection.h"
#include <iostream>

namespace http{
    namespace server{
      connection::connection(asio::ip::tcp::socket socket, connection_manager& manager)
      : socket_(std::move(socket)),
        connection_manager_(manager)
        {

        }
      

      void connection::start(){// read -> write
        do_read();
      }

      void connection::stop(){
        std::cout<<"stop"<<std::endl;
        socket_.close();
      }

      void connection::do_read(){
        socket_.async_read_some(
          asio::buffer(buffer_, sizeof(buffer_)),
          [this](std::error_code ec, std::size_t bytes_transferred){
            if(!ec){
              for(int i = 0;i<bytes_transferred;++i){
                std::cout<<buffer_[i];
              }
              do_write();
              do_read();
            }
            else{
              stop();
            }
          }
        );
      }

      void connection::do_write(){
        asio::async_write(socket_, asio::buffer(buffer_, sizeof(buffer_)),
          [this](std::error_code ec, std::size_t)
          {
            if (!ec)
            {
              // Initiate graceful connection closure.
              //asio::error_code ignored_ec;
              //socket_.shutdown(asio::ip::tcp::socket::shutdown_both,ignored_ec);
            }
            else{
              stop();
            }
            /*
            if (ec != asio::error::operation_aborted)
            {
              
              stop();
            }
            */
          });
      }

        
    }
}
