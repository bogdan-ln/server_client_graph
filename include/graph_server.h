#pragma once 
#include "libraries.h"

class Server{

public:
    Server(int port);
    ~Server();
    void run();
    void stop();

private:
    void client(boost::asio::ip::tcp::socket socket);
    std::vector<std::pair<double, double>> read_data(std::string filename);
    void send_len(boost::asio::ip::tcp::socket& socket, size_t len);
    void send_data(boost::asio::ip::tcp::socket& socket,const std::vector<std::pair<double, double>>& data);
    std::string reading_message(boost::asio::ip::tcp::socket& socket);
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor accept_;
    bool stoped;
};

