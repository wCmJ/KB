#pragma once
 
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#include <sstream>
#include <iostream>
#include <string>
#include <map>
 
#include <asio.hpp>
//#include <boost/array.hpp>
//#include <boost/bind.hpp>
 
 
namespace BoostSocket
{
	namespace SyncClient
	{
		enum { BUF_SIZE = 1024 };
		using asio::ip::tcp;
 
		class Client
		{
		public:
			Client(asio::io_context& ioc,
				const std::string& host, const std::string& port)
				: socket_(ioc), resolver_(ioc){
				
				asio::connect(socket_, 
					resolver_.resolve(asio::ip::tcp::v4(), host, port));
			}
 
			virtual ~Client(void) { socket_.close(); }
 
			int  SendData(const char* _buffer, std::size_t data_len){
				std::size_t reply_length = asio::write(socket_,
					asio::buffer(_buffer, data_len));
				return reply_length;
			}
 
			int	 RecvData(char* data, std::size_t read_len) {
				std::size_t reply_length = asio::read(socket_,
					asio::buffer(data, read_len));
				return reply_length;
			}
 
		public:
			asio::ip::tcp::socket socket_;
			asio::ip::tcp::resolver resolver_;
 
		private:
			std::string err_str_;
		};
 
		class ClientManager
		{
		public:
			ClientManager() {}
			~ClientManager() {}
 
		public:
			Client* get_client(const std::string& host, const std::string& port){
				return new Client(ioc_, host, port);
			}
 
 
		public:
			asio::io_context ioc_;
		};
 
	}//namespace SyncClient
}