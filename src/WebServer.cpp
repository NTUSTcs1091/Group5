// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "WebServer.h"

#include <boost/asio.hpp>

WebServer::WebServer(const std::string& ip, const int& port) {
    listener_ = std::make_unique<HttpListener>(&ioc_, ip, port);
}

void WebServer::run() {
    listener_->runAsync();
    // project will be block at here until all objects using ioc are close.
    ioc_.run();
}
