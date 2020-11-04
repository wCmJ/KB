#pragma once
 
#include "timer_client.h"


#include <iostream>
#include <string>
#include <vector>
 
namespace BoostSocket
{
 
	//同步客户端使用接口
	namespace SyncClient
	{
 
		class ClientManager;
		class Client;
 
		class ClientOper
		{
		public:
			virtual ~ClientOper() {}
 
			int  OpenClient(const std::string& host_name, const std::string & port);
			void CloseClient();
 
			int  SendData(const char* _buffer, std::size_t read_len);
			int  RecvData(char* data, std::size_t data_len);
 
		private:
			ClientManager*  oper_obj_;
			Client*  client_obj_;
 
		};
	}
}//namespace BoostSocket
 
//#include "Boost_Socket_Oper.h"
//#include "Client.h"
 
///
//*同步客户端*
//
int BoostSocket::SyncClient::ClientOper::OpenClient(const std::string & host_name, const std::string & port)
{
	try {
 
		oper_obj_ = new BoostSocket::SyncClient::ClientManager;
		// 构建Server实例
		client_obj_ = oper_obj_->get_client(host_name, port);
 
	}
	catch (std::exception& _e) {
		std::cout << _e.what() << std::endl;
		return -1;
	}
 
	return 0;
}
 
void BoostSocket::SyncClient::ClientOper::CloseClient()
{
	if (client_obj_ != nullptr)
	{
		delete client_obj_;
		client_obj_ = nullptr;
	}
 
}
 
int BoostSocket::SyncClient::ClientOper::SendData(const char* _buffer, std::size_t read_len)
{
	int nret = 0;
	try
	{
		nret = client_obj_->SendData(_buffer, read_len);
	}
	catch (std::exception& _e) {
		std::cout << _e.what() << std::endl;
		nret = -1;
	}
	return nret;
}
 
int BoostSocket::SyncClient::ClientOper::RecvData(char* data, std::size_t data_len)
{
	int nret = 0;
	try
	{
		nret = client_obj_->RecvData(data, data_len);
	}
	catch (std::exception& _e) {
		std::cout << _e.what() << std::endl;
		nret = -1;
	}
	return nret;
}