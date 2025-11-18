#pragma once 

#include <vector> 
#include <boost/asio.hpp>
#include <string>

class Server{

public:
    Server(int port);
    ~Server();
    void run();
    void stop();

private:
    void client(boost::asio::ip::tcp::socket socket);
    std::vector<std::pair<double, double>> read_data(std::string filename);
    void send_graph(boost::asio::ip::tcp::socket& socket, std::vector<std::pair<double, double>> data);
    void send_message(boost::asio::ip::tcp::socket& socket, std::string massage);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor accept_;
    bool stoped;
};

