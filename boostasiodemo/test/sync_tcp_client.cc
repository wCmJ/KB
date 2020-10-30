
#include "asio.hpp"

#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <vector>

using namespace asio;

io_service service;
ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);

size_t read_complete(char * buf, const error_code & err, size_t bytes)
{
    if ( err) return 0;
    bool found = std::find(buf, buf + bytes, '\n') < buf + bytes;
    // 我们一个一个读取直到读到回车，不缓存
    return found ? 0 : 1;
}
void sync_echo(std::string msg) {
    msg += "\n";
    ip::tcp::socket sock(service);
    sock.connect(ep);
    sock.write_some(buffer(msg));
    char buf[1024];
    //int bytes = read(sock, buffer(buf), std::bind(read_complete,buf,_1,_2));
    int bytes;
    std::string copy(buf, bytes - 1);
    msg = msg.substr(0, msg.size() - 1);
    std::cout << "server echoed our " << msg << ": "<< (copy == msg ? "OK" : "FAIL") << std::endl;
    sock.close();
}
int main(int argc, char* argv[]) {
    char* messages[] = { "John says hi", "so does James", "Lucy just got home", "Boost.Asio is Fun!", 0 };

    return 0;
}