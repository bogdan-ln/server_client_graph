#pragma once 
#include "libraries.h"

class Client {
public: 
    Client();
    ~Client();
    void connect();
    void send_message();
    std::vector<std::pair<double,double>> read_massege(boost::asio::ip::tcp::socket& socket);
    std::vector<std::pair<double,double>> make_arr(boost::asio::ip::tcp::socket& socket , size_t len);
    size_t make_len(boost::asio::ip::tcp::socket& socket);
    void make_graph(std::vector<std::pair<double, double>> data);
    void go(boost::asio::ip::tcp::socket socket);

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    std::string port_;

};