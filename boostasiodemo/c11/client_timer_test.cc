
#include "timer_client.h"
#include "timer_clientoper.h"
#include "timer.h"

using BoostSocket::SyncClient::ClientOper;
 
void time_out(ClientOper* client) {
	client->CloseClient();
}
 
int main(void)
{
	char request[1024] = { 0 };
	char reply[1024] = { 0 };
	std::vector<char> pBuf;
 
	std::size_t request_length = 0;
	do {
		std::cout << "Enter message: ";
		std::cin.getline(request, 1024);
		request_length = std::strlen(request);
	} while (request_length == 0);
 
 
	ClientOper client;
	int n = client.OpenClient("172.20.26.152", "13588");
	if (n < 0)
	{
		std::cout << "打开客户端失败!" << std::endl;
		client.CloseClient();
 
		system("pause");
		return -1;
	}
 
	int nret = client.SendData(request, request_length);
	if (nret < 0)
	{
		std::cout << "发送数据失败!" << std::endl;
		client.CloseClient();
 
		system("pause");
		return -1;
	}
 
	std_timer timer;
	//同步
	timer.AsyncWait(3000, time_out, &client);
 
	int nlen = client.RecvData(reply, request_length);
	if (nlen < 0)
	{
		std::cout << "接收数据失败!" << std::endl;
		client.CloseClient();
 
		system("pause");
		return -1;
	}
 
	std::cout << reply << std::endl;
	std::cout << nret << " " << nlen << std::endl;
 
	client.CloseClient();
 
	system("pause");
	return 0;
}