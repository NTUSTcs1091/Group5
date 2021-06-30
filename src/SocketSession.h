// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. 

#ifndef GROUP5_SRC_SOCKETSESSION_H_	
#define GROUP5_SRC_SOCKETSESSION_H_
#include <boost/asio.hpp>  

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>

#include "HttpUtility.h"
#include "SocketUtility.h"


/** @brief Handle the upgrading http request*/
class SocketSession : public std::enable_shared_from_this<SocketSession> {
private:
	/** @brief socket id.*/
	boost::asio::ip::tcp::socket socket_;

	/** @brief wsframe want to be send*/
	std::string sended_msg_="";
	
	/** @brief buffer for boost::asio::async_read*/
	boost::asio::streambuf buffer_;

	std::queue<std::string> queue_;

	/** @brief Receive message from client*/
	void receiveMessage();
	
	/** @brief Handle SocketMessage.
	 *  @param message Decoded SocketMessage. This is called by receiveMessage() after the entire socket message has been received.
	 */
	void receiveMessageHandler(const boost::system::error_code& ec, std::size_t bytes);

	/** @brief send the message
	 *  @param msg text want to be send.
	 */
	void sendMessage(const std::string &msg);

	/** @brief Handler after message be sended.
	 *  @param ec System-specific errors bytes_transferred 
	 */
	void sendMessageHandler(const boost::system::error_code& ec, std::size_t bytes_transferred);

	/** @brief Package Response and Send.
	 *  @param ec System-specific errors what Show what function error
	 */
	void handleFail(boost::system::error_code ec, char const* what);

public:
	// http_request_(request) maybe we do not need to do it?
	SocketSession(boost::asio::ip::tcp::socket&& socket) :socket_(std::move(socket)) {}
	SocketSession(const SocketSession &) = delete;
	SocketSession& operator=(const SocketSession&) = delete;

	/** @brief Run socketSession after initial.*/
	void runAsync();

	/** @brief  public function of sendMessage*/
	void sendMessagePublic(const std::string &msg);

	/** @brief Close webSocket session.*/
	void close(boost::system::error_code ec);
};
#endif
