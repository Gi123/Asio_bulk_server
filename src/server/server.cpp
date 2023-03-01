#include "server.h"
#include <iostream>
#include <memory>

Server::Server(const size_t port, const size_t _bulk_size) :
    bulk_size(_bulk_size), _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        accept();
        io_context.run();
    }

Server::~Server(){};
void Server::accept() {
    _acceptor.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
        if(!ec){
            std::make_shared<Session>(std::move(socket), bulk_size)->start();
        }else
            std::cerr << "Code Error: " << ec.message() << std::endl;
        accept();
    });
}


Session::Session(boost::asio::ip::tcp::socket socket, const size_t _bulk_size) :
    socket_(std::move(socket)), bulk_size(_bulk_size) {
        h = async::connect(bulk_size);
}
Session::~Session(){};

void Session::start() {
    read();
}

void Session::read() {
    auto self(shared_from_this());
    //auto inputHandler = [this, self](boost::system::error_code ec, std::size_t length) {
        socket_.async_read_some(boost::asio::buffer(data, 1024), 
        [this, self](boost::system::error_code ec, std::size_t length) {
        if(!ec && length > 0) {
            std::string toParse(data, length);
            std::istringstream commandSequence;
            commandSequence.str(toParse);

            std::string command;
            while (std::getline(commandSequence, command, '\n')) { //there may be more than one command in the rawInput
                async::receive(h, command.c_str(), command.length());
            }
            read();
            
        } else {

            async::disconnect(h);
        }
        });

}