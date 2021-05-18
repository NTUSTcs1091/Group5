// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "HttpListener.h"

#include <iostream>

#include "HttpSession.h"

HttpListener::HttpListener(boost::asio::io_context* const ioc, const std::string& ip, const int& port)
    : ioc_(ioc)
    , acceptor_(*ioc)
    , accept_socket_(*ioc) {
    boost::system::error_code ec;
    // create endpoint
    const auto address = boost::asio::ip::make_address(ip);
    boost::asio::ip::tcp::endpoint endpoint(address, port);
    // create acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if (ec) {
        handleFail(ec, "open");
        return;
    }
    acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
    if (ec) {
        handleFail(ec, "set_option");
        return;
    }
    acceptor_.bind(endpoint, ec);
    if (ec) {
        handleFail(ec, "bind");
        return;
    }
    acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
    if (ec) {
        handleFail(ec, "listen");
        return;
    }
}

void HttpListener::runAsync() {
    acceptor_.async_accept(accept_socket_,
        std::bind(
            &HttpListener::handleAccept,
            this,
            std::placeholders::_1
    ));
}

void HttpListener::handleFail(const boost::system::error_code& ec, const std::string& msg) {
    // Don't report on canceled operations
    if (ec == boost::asio::error::operation_aborted)
        return;
    std::cerr << msg << ": " << ec.message() << "\n";
}

void HttpListener::handleAccept(const boost::system::error_code& ec) {
    if (ec) {
        handleFail(ec, "accept");
        return;
    }
    makeHttpSession();
    runAsync();
}

void HttpListener::makeHttpSession() {
    std::make_shared<HttpSession>(
        std::move(accept_socket_))->runAsync();
}
