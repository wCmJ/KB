#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

#include <unordered_set>
#include "connection.h"

namespace http{
namespace server{

class connection_manager{
public:
    connection_manager(const connection_manager&) = delete;
    connection_manager& operator=(const connection_manager&) = delete;

    connection_manager();

    void start(connection_ptr);

    void stop(connection_ptr);

    void stop_all();

private:

    std::unordered_set<connection_ptr> connections_;
};


}}

#endif

