// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_HTTPSESSION_H_	
#define HTTPLIB_SRC_HTTPSESSION_H_	

#include <boost/asio.hpp>

#include <string>
#include <vector>

#include "SocketSession.h"
#include "HttpUtility.h"
class SocketSession;

/** @brief Handle the incoming http request. */
class HttpSession {
private:
    /** @brief socket fd.*/
    boost::asio::ip::tcp::socket socket_;
    /** @brief Receive stream package.This is a callback for read_async() in asio
     *  @param msg Stream package's content.
     */
    void receiveMessage(const std::vector<boost::asio::const_buffer> &msg);
    /** @brief Handle HttpRequest. This is called after receiveMessage() after the entire http request has been received.
     *  @param request Decoded HttpRequest.
     */
    void handleRequest(const HttpUtility::Request &request);
    /** @brief Package Response and Send.
     *  @param response Decoded HttpResponse.
     */
    void sendMessage(const HttpUtility::Response &response);
    /** @brief Return true if this is upgraded to websocket */
    bool isUpgrade();

public:

    explicit HttpSession(boost::asio::ip::tcp::socket&& socket);
    HttpSession(const HttpSession &) = delete;
    HttpSession& operator=(const HttpSession&) = delete;

    /** @brief Run HttpSession after initial.*/
    void run();

    /** @brief Close HttpSession.*/
    void close();

    
};
#endif
