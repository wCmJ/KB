#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "asio.hpp"

#include <memory>
//#include "connection_manager.h"




namespace http{
namespace server{

class connection_manager;

class connection{
public:
    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;

    explicit connection(asio::ip::tcp::socket, connection_manager& manager);

    void start();

    void stop();

private:
    void do_read();

    void do_write();

    char buffer_[8192];

    asio::ip::tcp::socket socket_;

    connection_manager& connection_manager_;

};

typedef std::shared_ptr<connection> connection_ptr;

}}

#endif