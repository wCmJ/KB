
#include "connection_manager.h"


namespace http{
namespace server{

connection_manager::connection_manager(){

}

void connection_manager::start(connection_ptr conn){
    connections_.insert(conn);
    conn->start();
}

void connection_manager::stop(connection_ptr conn){
    connections_.erase(conn);
    conn->stop();
}

void connection_manager::stop_all(){
    for(auto conn: connections_){
        conn->stop();
    }
    connections_.clear();
}

}
}

