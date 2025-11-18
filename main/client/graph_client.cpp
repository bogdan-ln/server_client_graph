#include "graph_client.h"
#include <iostream> 
#include <string> 
#include <boost/asio.hpp> 

Client::Client(): socket_(io_context_){}

Client::~Client() {

}

void Client::connect(){
    boost::asio::ip::tcp::endpoint ep(
        boost::asio::ip::make_address("127.0.0.1"), 
        8080
    );
    socket_.connect(ep);
    std::string command;
    std::getline(std::cin, command);
    command += "\n";
    boost::asio::write(socket_, boost::asio::buffer(command));
}
