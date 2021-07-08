// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_HTTPSESSION_H_	
#define HTTPLIB_SRC_HTTPSESSION_H_	

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "HttpUtility.h"
#include "SocketSession.h"

/** @brief Handle the incoming http request. */
class HttpSession : public std::enable_shared_from_this<HttpSession> {
private:
    /** @brief socket fd.*/
     boost::asio::ip::tcp::socket socket_;

	/** @brief http request */
	 HttpUtility::HttpRequest request;
	
	/** @brief messege want to be send*/
	std::string handshake_msg_ = "";
	
	/** @brief buffer for boost::asio::async_read*/
	boost::asio::streambuf buffer_;
	
	/** @brief Receive message from client*/
	void receiveMessage();

    /** @brief Handle HttpRequest  This is called after receiveMessage() after the entire http request has been received.
     *  @param ec System-specific errors. bytes 
     */
    void receiveMessageHandler(const boost::system::error_code& ec, std::size_t bytes);
    
	/** @brief Package send http response.
	 *  @param isUpgrade isUpgrade to websocket  or not
	 */
	void sendMessage(bool isUpgrade);
	
	/** @brief Handler after send response.
     *  @param response Decoded HttpResponse.
     */
	void sendMessageHandler(const boost::system::error_code& ec, std::size_t bytes_transferred);
    
	/** @brief open the socketsession idf upgraded */
	void  makeSocketSession();

	/** @brief Return true if this is upgraded to websocket */
    bool isUpgrade();

	/** @brief Package Response and Send.
	 *  @param ec System-specific errors what Show what function error
	 */
	void handleFail(boost::system::error_code ec, char const* what);

public:

	explicit HttpSession(boost::asio::ip::tcp::socket&& socket):socket_(std::move(socket)) {}
    HttpSession(const HttpSession &) = delete;
    HttpSession& operator=(const HttpSession&) = delete;

    /** @brief Run HttpSession after initial.*/
    void runAsync();

    /** @brief Close HttpSession.*/
    void close(boost::system::error_code ec);

};
#endif