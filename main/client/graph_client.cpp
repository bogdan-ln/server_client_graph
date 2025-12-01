#include "libraries.h"

Client::Client() : socket_(io_context_){}

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
    go(std::move(socket_));
}

size_t Client::make_len(boost::asio::ip::tcp::socket& socket){
    size_t len;
    boost::asio::read(socket, boost::asio::buffer(&len, sizeof(len)));
    std::cout << len << std::endl;
    std::string command = "d\n";
    boost::asio::write(socket, boost::asio::buffer(command));
    return len;
}

std::vector<std::pair<double,double>> Client::make_arr(boost::asio::ip::tcp::socket& socket, size_t len){
    std::vector<std::pair<double, double>> data;
    data.resize(len);
    boost::asio::read(socket, boost::asio::buffer(data.data(), len * sizeof(std::pair<double, double>)));
    std::cout << data.size()<< std::endl;
    return data;
}

void Client::make_graph(std::vector<std::pair<double, double>> data){
    std::vector<double> x;
    std::vector<double> y ;
    x.reserve(data.size());
    y.reserve(data.size());
    int len = data.size();
    for(auto point : data) {
        x.push_back(point.first);
        y.push_back(point.second);
    }
    Graph g;
    //g.label = "График зависимости x, y";
    g.graph(x,y);
    g.show(-1);
}
void Client::go(boost::asio::ip::tcp::socket socket){
    size_t len = make_len(socket);
    std::vector<std::pair<double,double>> data;
    make_graph(make_arr(socket, len));
}
