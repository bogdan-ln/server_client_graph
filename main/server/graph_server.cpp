#include <vector>
#include <string> 
#include "graph_server.h"
#include "graph.hpp"
#include "boost/asio.hpp"
#include <fstream>
#include <iostream>
#include <istream> 

Server::Server (int port) 
    :accept_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    , stoped(false)
{
    std::cout <<"Сервер ожидает клиента"<<std::endl;
}

Server::~Server() {
    stop();
}

void Server::run() {
    while(!stoped){
        boost::asio::ip::tcp::socket socket(io_context_);
        accept_.accept(socket);
        if (stoped) {
            break;
        }
        client(std::move(socket));
    }
}

void Server::stop() {
    stoped = true;
    accept_.close();
    io_context_.stop();
}

std::vector<std::pair<double, double>> Server::read_data(std::string filename){
    std::vector<std::pair<double, double>> data;
    std::ifstream file(filename);
    double x, y;
    while(file >> x >> y) { 
        data.push_back({x,y});
    }
    file.close();
    if (data.size() == 0) { 
        std::cout<< "Ошибка чтения" << std::endl;
        data.push_back({1,1});
    }
    return data;
}

void Server::send_message(boost::asio::ip::tcp::socket& socket, std::string message){
    boost::asio::write(socket , boost::asio::buffer(message + "\n"));
}

void Server::send_graph(boost::asio::ip::tcp::socket& socket, std::vector<std::pair<double, double>> data){
    try{
        std::vector<double> x;
        std::vector<double> y ;
        x.reserve(data.size());
        y.reserve(data.size());
        int len = data.size();
        for(const auto& point : data) {
            x.push_back(point.first);
            y.push_back(point.second);
        }
        Graph g;
        // g.label = "График зависимости x, y";
        g.graph(x,y);
        g.show(-1);
    }catch( const std::exception&e){
        std::cout <<"ошибка при отображении графика"<<e.what() << std::endl;
    }
}

void Server::client(boost::asio::ip::tcp::socket socket){
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, '\n');
    std::istream input(&buffer);
    std::string command;
    std::getline(input, command);
    std::cout << "Получена команда: '" << command << "'" << std::endl;
    if (command == "show_graph") { 
        std::vector<std::pair<double, double>> data = read_data("input.txt");
        send_graph(socket, data);
        std::cout <<"Графи котправлен"<<std::endl;
    }
    else {
        send_message(socket, "непонятная команда, надо исспользовать show_graph");
    }
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
}
