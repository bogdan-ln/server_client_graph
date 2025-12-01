#include "libraries.h"

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
        client(static_cast<boost::asio::ip::tcp::socket &&>(socket));
        socket.close();
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
std::string Server::reading_message(boost::asio::ip::tcp::socket& socket){
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, '\n');
    std::string command;
    std::istream input(&buffer);
    std::getline(input, command);
    return command;
}

void Server::send_len(boost::asio::ip::tcp::socket& socket, size_t len){
    boost::asio::write(socket, boost::asio::buffer(&len, sizeof(len)));
}

void Server::send_data(boost::asio::ip::tcp::socket& socket, std::vector<std::pair<double, double>> data){
    size_t len = data.size();
    boost::asio::write(socket, boost::asio::buffer(data.data(), len * sizeof(std::pair<double, double>)));
}

void Server::client(boost::asio::ip::tcp::socket socket){
    std::string command_1 = reading_message(socket);
    std::cout << "Получена команда: '" << command_1 << "'" << std::endl;
    if (command_1== "show_graph") {                                                  //enum class
        std::vector<std::pair<double, double>> data = read_data("input.txt");
        send_len(socket, data.size());
        std::cout << "Отправлена длинна"<< std::endl;
        std::string command_2 = reading_message(socket);

        if(command_2 == "d"){
            send_data(socket, data);
        }
    }
    //socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
}
