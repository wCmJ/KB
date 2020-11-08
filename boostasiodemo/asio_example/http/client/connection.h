#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "asio.hpp"

namespace http{
namespace client
{
class connection{
public:
    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;
    connection(asio::ip::tcp::socket);
    void start();
    void stop();
private:
    void do_read();
    void do_write();
    void make_message();
    asio::ip::tcp::socket socket_;
    char send_buffer_[8192], receive_buffer_[8192];
    std::size_t send_message_len, receive_message_len;
};

} // namespace client
} // namespace http


#endif