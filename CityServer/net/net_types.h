#pragma once

#include <memory>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

namespace net {

    using IoService                     = boost::asio::io_service;
    using Acceptor                      = boost::asio::ip::tcp::acceptor;
    using TcpSocket                     = boost::asio::ip::tcp::socket;
    using TcpSocketPtr                  = std::shared_ptr<TcpSocket>;

}
