// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "SocketSession.h"

typedef boost::asio::buffers_iterator<boost::asio::streambuf::const_buffers_type> iterator;
std::pair<iterator, bool> match_end_socket(iterator begin, iterator end) {
	int index = 0;
	uint8_t fin= 0x00;
	iterator i = begin;
	//print hexa decimal of data
	while (i != end) {
		//std::cout << std::hex << (int)(*i)<<" ";
		if (index == 0)
			fin = (uint8_t)((*i) >> 7) & 0x01;
		index++;
		i++;
	}
	//fin = (uint8_t)((*i) >> 7) & 0x01;
	std::cout << std::endl;
	if (fin == 0x01){
		return std::make_pair(i, true);
	}
	else{
		return std::make_pair(i, false);
	}	
}

void SocketSession::receiveMessage() {
	std::cout << "receive" << std::endl;

	buffer_.consume(buffer_.size());
	boost::asio::async_read_until(
		socket_,
		buffer_,
		match_end_socket,
		std::bind(
			&SocketSession::receiveMessageHandler,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2
		)
	);
}

void SocketSession::receiveMessageHandler(const boost::system::error_code& ec, std::size_t bytes) {
	std::cout << "HandleMessage" << std::endl;
	// Handle the error, if any
	if (ec) {
		handleFail(ec, "Socket Read");
		close(ec);
		return;
	}
	//Handle Message
	std::string buffer((std::istreambuf_iterator<char>(&buffer_)), std::istreambuf_iterator<char>());
	SocketUtility::Frame wsFrame = SocketUtility::DecodeMessage(buffer);
	if (wsFrame.opcode == 0x8) {
		std::cout << "Close Connect" << std::endl;
		close(ec);
	}
	else {
		std::cout << wsFrame.Payload << std::endl;
		sendMessage("OK boy");
	}
	//receiveMessage();
}

void SocketSession::sendMessage(const std::string &msg) {
	SocketUtility::Frame wsFrame;	
	wsFrame.fin = 0x1;
	wsFrame.opcode = 0x1;
	wsFrame.Mask = 0x0;
	wsFrame.PayloadLen = msg.length();
	for (int i = 0; i < 4; i++) {
		wsFrame.Maskingkey[i] = static_cast<char>(rand() % 0xff);;
	}
	wsFrame.Payload= new char[wsFrame.PayloadLen];
	for (int i = 0; i < wsFrame.PayloadLen; i++) {
		wsFrame.Payload[i] = msg[i];
	}
	//Encode
	sended_msg_ = "";
	sended_msg_ = SocketUtility::EncodeMessage(wsFrame);
	//Async_Write
	boost::asio::async_write(
		socket_,
		//boost::asio::buffer(response),
		boost::asio::buffer(sended_msg_),
		std::bind(
			&SocketSession::sendMessageHandler,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2)
	);
}

void SocketSession::sendMessageHandler(const boost::system::error_code& ec, std::size_t bytes_transferred) {
	if (ec) {
		handleFail(ec, "Socket Send");
		close(ec);
		return;
	}
	sended_msg_ = "";
	//if (!queue_.empty()) {
	//	sendMessage();
	//}
	receiveMessage();
}

void SocketSession::handleFail(boost::system::error_code ec, char const* what) {
	std::cerr << what << ": " << ec.message() << "\n";
}

void  SocketSession::runAsync() {
	receiveMessage();
}

void SocketSession::sendMessagePublic(const std::string &msg) {
	sendMessage(msg);
}

void SocketSession::close(boost::system::error_code ec) {
	std::cout << "Close Socket  " << ec << "\n";
	socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
}

