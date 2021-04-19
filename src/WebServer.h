// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_WEBSERVER_H
#define HTTPLIB_SRC_WEBSERVER_H

#include <memory>
#include <string>

#include <boost/asio.hpp>

#include "HttpListener.h"

/** @brief Do project initialize and run. */
class WebServer {
private:
    static constexpr char kIP[] = "127.0.0.1";
    static constexpr int kPort = 80;
private:
    /** @brief Required for I/O. */
    boost::asio::io_context ioc_;
    /** @brief Request listener. */
    std::unique_ptr<HttpListener> listener_;
public:
    WebServer(const std::string& ip = WebServer::kIP, const int& port = WebServer::kPort);
    /** @brief Non construction-copyable. */
    WebServer(const WebServer&) = delete;
    /** @brief Non copyable. */
    WebServer& operator=(const WebServer&) = delete;
    /** @brief Project runner. */
    void run();
};

#endif
