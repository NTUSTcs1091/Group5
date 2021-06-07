// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_HTTPUTILITY_H_	
#define HTTPLIB_SRC_HTTPUTILITY_H_	

#include <boost/asio.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "StringUtility.h"
#include "SocketUtility.h"
namespace HttpUtility {
	typedef struct {
		std::string Method;
		std::string URL;
		std::string version;
		std::string Host;
		std::string Connection;
		std::string Upgrade;
		std::string cookie;
		std::map<std::string, std::string> param;
		std::string SecWebSocketKey;
		std::string content;
	}HttpRequest;

	/** @brief Decode raw string to HttpRequest structure.
	 *  @param buffer The full string sended by client.
	 */
	HttpRequest DecodeRequest(const std::string &buffer);

	/** @brief Package Response and Send.
		 *  @param response Decoded HttpResponse.
		 */
	std::string EncodeResponse(const HttpRequest &request, const bool &isUpgrade);
}
#endif
