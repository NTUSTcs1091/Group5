// Copyright (c) 2021,Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "HttpSession.h"

typedef boost::asio::buffers_iterator<boost::asio::streambuf::const_buffers_type> iterator;
std::pair<iterator, bool> match_end(iterator begin, iterator end) {
	int index = 0;
	const std::string match = "\r\n\r\n";
	iterator i = begin;
	while (i != end) {
		if (*i == match[index])
			index++;
		else
			index = 0;
		if (index == 4)
			return std::make_pair(i, true);
		i++;
	}
	return std::make_pair(i, false);
}

void HttpSession::receiveMessage() {
	buffer_.consume(buffer_.size());
	boost::asio::async_read_until(
		socket_,
		buffer_,
		match_end,
		std::bind(
			&HttpSession::receiveMessageHandler,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2
		)
	);
}

void HttpSession::receiveMessageHandler(const boost::system::error_code& ec, std::size_t bytes) {
	// Handle the error, if any
	if (ec) {
		handleFail(ec, "Http Read");
		close(ec);
		return;
	}
	boost::ignore_unused(bytes);

	// convert parser data to string data.
	std::string buffer((std::istreambuf_iterator<char>(&buffer_)), std::istreambuf_iterator<char>());
	std::cout << buffer << std::endl;
	request = HttpUtility::DecodeRequest(buffer);

	if (isUpgrade()) {
		sendMessage(isUpgrade());
	}
	else {
		close(ec);
	}
}

void HttpSession::sendMessage(bool isUpgrade) {
	handshake_msg_ = HttpUtility::EncodeResponse(request,isUpgrade);
	boost::asio::async_write(
		socket_,
		boost::asio::buffer(handshake_msg_),
		std::bind(
			&HttpSession::sendMessageHandler,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2));
}


void HttpSession::sendMessageHandler(const boost::system::error_code& ec, std::size_t bytes_transferred) {
	if (ec) {
		handleFail(ec, "Http Send");
		close(ec);
	}
	makeSocketSession();
}

void HttpSession::makeSocketSession() {
	std::make_shared<SocketSession>(std::move(socket_))->runAsync();
}

bool HttpSession::isUpgrade() {
	if (request.Connection.find("Upgrade") != std::string::npos && request.Upgrade.find("websocket") != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}

void HttpSession::handleFail(boost::system::error_code ec, char const* what) {
	if (ec == boost::asio::error::operation_aborted)
		return;
	std::cerr << what << ": " << ec.message() << "\n";
}

void HttpSession::runAsync() {
	receiveMessage();
}

void HttpSession::close(boost::system::error_code ec) {
	std::cout << "Close Socket" << std::endl;
	socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
}
