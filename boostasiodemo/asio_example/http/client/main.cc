#include "client.h"
#include <iostream>


int main(int argc, char* argv[]){
    std::cout<<"argc: "<<argc<<std::endl;
    if(argc < 3){
        std::cout<<"Usage: ./main <server_host> <port>\n";
        return 1;
    }

    {
        asio::io_context io_context_;
        asio::ip::tcp::socket socket(io_context_);
        asio::ip::tcp::resolver resolver(io_context_);
        asio::ip::tcp::endpoint ep = *resolver.resolve(argv[1], argv[2]).begin();
        socket.connect(ep);
        while(true){
            //std::cout<<"send message"<<std::endl;
            std::string mess = "suspend";
            socket.send(asio::buffer(mess));
            char buf[512];
            auto len = socket.receive(asio::buffer(buf, sizeof(buf)));
            for(int i = 0;i<len;++i){
                std::cout<<buf[i];
            }
            std::cout<<std::endl;
            sleep(1);
        }

        return 0;
    }


    try{
        http::client::client cli(argv[1], argv[2]);
        cli.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }
    return 0;
}
