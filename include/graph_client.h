#pragma once 
#include <boost/asio.hpp>
#include <string>

class Client {
public: 
    Client();
    ~Client();
    void connect();
    void send_message();

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    std::string port_;

};