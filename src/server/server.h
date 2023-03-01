#include "async.h"

#include <boost/asio.hpp>
#include <memory>
#include <utility>
#include <array>

class Session: public std::enable_shared_from_this<Session> {
    boost::asio::ip::tcp::socket socket_;
    const size_t bulk_size;
    void* h;
    char data[1024];
public:
    Session(boost::asio::ip::tcp::socket socket, const size_t _bulk_size);
    ~Session();
    void start();
private:
    void read();
};

class Server
{
private:
    const size_t bulk_size;
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor _acceptor;
public:
    Server(const size_t _port, const size_t _bulk_size);
    ~Server();
    void accept();
};

