// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_HTTPLISTENER_H
#define HTTPLIB_SRC_HTTPLISTENER_H

#include <string>

#include <boost/asio.hpp>

/** @brief Create server socket for listening incoming http request. */
class HttpListener {
private:
    /** @brief Required for I/O. */
    boost::asio::io_context *ioc_;
    /** @brief Acceptor socket. */
    boost::asio::ip::tcp::socket accept_socket_;
    /** @brief Wait and Accept new connection. */
    boost::asio::ip::tcp::acceptor acceptor_;
    /** @brief Handle fail state.
     *  @param ec Boost error code.
     *  @param msg Custom error message.
     */
    void handleFail(const boost::system::error_code& ec, const std::string& msg);
    /** @brief Handle accept state.
     *  @param ec Boost error code.
     */
    void handleAccept(const boost::system::error_code& ec);
    /** @brief Create HttpSession class object. 
     *  
     *  After acceptor_ accept a new connection, it will create HttpSession for 
     *  handling request and response by the use of accept_socket_.
     *  
     */
    void makeHttpSession();
public:
    HttpListener(boost::asio::io_context* const ioc, const std::string& ip, const int& port);
    /** @brief Non construction-copyable. */
    HttpListener(const HttpListener&) = delete;
    /** @brief Non copyable. */
    HttpListener &operator=(const HttpListener&) = delete;
    /** @brief Wait for accept asynchronously. */
    void runAsync();
};

#endif
