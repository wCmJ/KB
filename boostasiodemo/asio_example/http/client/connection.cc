#include "connection.h"
#include <iostream>


namespace http{
namespace client
{
    connection::connection(asio::ip::tcp::socket socket):socket_(std::move(socket)), send_message_len(0),receive_message_len(0){
        std::string mes = "client message: ";
        send_message_len = mes.size() + 1;
        for(int i = 0;i<mes.size();++i){
            send_buffer_[i] = mes[i];
        }
        start();
    }

    void connection::start(){
        do_write();
    }

    void connection::stop(){
        socket_.close();
    }

    void connection::make_message(){
        static int cnt = 0;
        send_buffer_[send_message_len - 1] = (char)(cnt + '0');
        ++cnt;
    }

    void connection::do_write(){
        std::cout<<"do_write"<<std::endl;
        sleep(2);
        make_message();
        socket_.async_send(
            asio::buffer(send_buffer_, send_message_len),
            [this](std::error_code ec, std::size_t send_len){
                if(!ec){
                    do_read();
                    do_write();
                }
                else{
                    stop();
                }
            }
        );
    }

    
    void connection::do_read(){
        socket_.async_read_some(
            asio::buffer(receive_buffer_, sizeof(receive_buffer_)),
            [this](std::error_code ec, std::size_t receive_len){
                if(!ec){
                    for(int i = 0;i<receive_len;++i){
                        std::cout<<receive_buffer_[i];
                    }
                    std::cout<<std::endl;
                }
                else{
                    stop();
                }
            }
        );
    }

} // namespace client
} // namespace http