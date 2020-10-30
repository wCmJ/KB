
#include "asio.hpp"

#include <iostream>
#include <thread>

void tcp_sync_rw(){//在一个tcp socket上进行同步读写
    asio::io_service service;
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 2002);
    asio::ip::tcp::socket sock_tcp(service);
    sock_tcp.connect(ep);
    sock_tcp.write_some(asio::buffer("Hello\n"));
    std::cout<<"bytes available" << sock_tcp.available() << std::endl;
    char buff[512];
    size_t read = sock_tcp.read_some(asio::buffer(buff));
}

void udp_sync_rw(){//在一个udp socket上进行同步读写
    
    
    std::cout<<"child-1"<<std::endl;
    asio::io_service service;
    asio::ip::udp::socket sock_udp(service);
    sock_udp.open(asio::ip::udp::v4());
    asio::ip::udp::endpoint receiver_ep(asio::ip::address::from_string("127.0.0.1"), 2002);
    sock_udp.send_to(asio::buffer("testing\n"), receiver_ep);
    char buff[512];
    asio::ip::udp::endpoint sender_ep;
    sock_udp.receive_from(asio::buffer(buff), sender_ep);
    std::cout<<"client end"<<std::endl;

}

//从一个udp服务套接字中异步读取数据
using namespace asio;
io_service service;
ip::udp::socket sock(service);
ip::udp::endpoint sender_ep;
char buff[512];
void on_read(const asio::error_code & err, std::size_t read_bytes) {
  std::cout << "read " << read_bytes << std::endl;
  std::cout << "server receive data is: " << buff << std::endl;
  sock.async_receive_from(buffer(buff), sender_ep, on_read);
}

int main(int argc, char* argv[]) {
  std::cout<<"main start"<<std::endl;
  //ip::udp::endpoint ep(ip::address::from_string("127.0.0.1"), 2002);
  ip::udp::endpoint ep;
  ep = ip::udp::endpoint(ip::address::from_string("127.0.0.1"), 2002);
  sock.open(ep.protocol());
  sock.set_option(ip::udp::socket::reuse_address(true));
  sock.bind(ep);
  std::cout<<"1"<<std::endl;
  std::thread client_thread(udp_sync_rw);
  sock.async_receive_from(buffer(buff,512), sender_ep, on_read);
  service.run();
  std::cout<<"2"<<std::endl;
  client_thread.join();
  std::cout<<"client join end"<<std::endl;
  return 0;
}

