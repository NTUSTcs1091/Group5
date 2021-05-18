// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. 

#ifndef GROUP5_SRC_SOCKETSESSION_H_	
#define GROUP5_SRC_SOCKETSESSION_H_
#include <boost/asio.hpp>  

#include <string>
#include <vector>

#include "SocketUtility.h"

/** @brief Handle the upgrading http request*/
class SocketSession {
private:
    /** @brief socket id.*/
    boost::asio::ip::tcp::socket socket_;

    /** @brief Receive stream package.
     *  @param msg stream package's content. This is a callback for read_async() in asio.
     */
    void receiveMessage(const std::vector<boost::asio::const_buffer> &msg);

    /** @brief Handle SocketMessage.
     *  @param message Decoded SocketMessage. This is called by receiveMessage() after the entire socket message has been received.
     */
    void handleMessage(const SocketUtility::WSMessage &message);
    /** @brief Package Message and Send.
     *  @param message Decoded SocketMessage.
     */
    void sendMessage(const SocketUtility::WSMessage &message);

public:
    SocketSession(boost::asio::ip::tcp::socket&& _socket);
    SocketSession(const SocketSession &) = delete;
    SocketSession& operator=(const SocketSession&) = delete;

    /** @brief Run socketSession after initial.*/
    void run();
    /** @brief Close webSocket session.*/
    void close();

    
};
#endif
