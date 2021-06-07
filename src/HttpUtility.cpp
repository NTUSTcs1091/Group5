// Copyright (c) 2021,Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "HttpUtility.h"

HttpUtility::HttpRequest HttpUtility::DecodeRequest(const std::string &buffer) {
	HttpRequest request;
	std::cout << "http Message : \n" << buffer << std::endl;
	std::vector<std::string> httpStrs = StringUtility::split(buffer, "\r\n");
	for (size_t i = 0; i < httpStrs.size(); i++) {
		if (i == 0) {
			std::vector<std::string> requestTop = StringUtility::split(httpStrs.at(i), " ");
			request.Method = requestTop.at(0);
			std::transform(request.Method.begin(), request.Method.end(), request.Method.begin(), toupper);
			request.URL = requestTop.at(1);
			request.version = requestTop.at(2);

			if (request.URL.find("?") != std::string::npos) {
				std::string content = StringUtility::split(request.URL, "?").at(1);
				std::vector<std::string> paramStrs = StringUtility::split(content, "&");
				for (std::vector<std::string>::iterator iter = paramStrs.begin(); iter != paramStrs.end(); iter++) {
					std::vector<std::string> paramStr = StringUtility::split(*iter, "=");
					request.param.insert(std::pair<std::string, std::string>(paramStr.at(0), paramStr.at(1)));
				}
			}
		}
		else if (i > 0 && i < httpStrs.size() - 1) {
			std::vector<std::string> requestHead = StringUtility::split(httpStrs.at(i), ": ");
			if (httpStrs.at(i).find("Host") != std::string::npos) {
				request.Host = requestHead.at(1);
			}
			else if (httpStrs.at(i).find("Connection") != std::string::npos) {
				request.Connection = requestHead.at(1);
			}
			else if (httpStrs.at(i).find("Upgrade") != std::string::npos) {
				request.Upgrade = requestHead.at(1);
			}
			else if (httpStrs.at(i).find("Sec-WebSocket-Key") != std::string::npos) {
				request.SecWebSocketKey = requestHead.at(1);
			}
		}
		else if (i == httpStrs.size() - 1) {
			request.content = httpStrs.at(i);
		}
	}
	return request;
}

std::string HttpUtility::EncodeResponse(const HttpUtility::HttpRequest &request, const bool &isUpgrade)
{
	std::string response = "";
	if (isUpgrade) {
		std::string SecWebSocketAccept = SocketUtility::generateAcceptKey(request.SecWebSocketKey);
		response.append("HTTP/1.1 101 Switching Protocols\r\n");
		response.append("Upgrade: websocket\r\n");
		response.append("Connection: Upgrade\r\n");
		response.append("Sec-WebSocket-Accept: " + SecWebSocketAccept + "\r\n");
		response.append("\r\n");
	}
	else {
		response.append("HTTP/1.1 200 OK\r\n");
		response.append("Content-Type: text/html;charset=ANSI\r\n");
		response.append("Server: wxj233\r\n");
		response.append("Connection: close\r\n");
		response.append("\r\n");
	}
	return response;
}

