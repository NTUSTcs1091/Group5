// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_SOCKETUTILITY_H
#define HTTPLIB_SRC_SOCKETUTILITY_H

#include <string>
#include <vector>

/** @brief Socket utility functions */
namespace SocketUtility {
    /** @brief Store data frame */
    typedef struct {
        // 狀態
        // 0 : 表示結束
        // 1 : 表示還有資料
        uint8_t fin;
        // 控制碼
        // 0x0 : 繼續
        // 0x1 : char frame
        // 0x2 : binary frame
        // 0x8 : shut down
        // 0x9 : ping
        // 0xA : pong
        uint8_t opcode;
        uint8_t Mask;
        uint8_t PayloadLen;
        char  Maskingkey[4];
        char* Payload;
    } Frame;
    /** @brief Store data frames */
    typedef struct {
        std::vector<Frame> frames;
    } WSMessage;

    /** @brief Parse message string to readable information.
     *  @param message Message that receive from client.
    */
    WSMessage parseMessage(const std::string& message);
    /** @brief Generate Sec-WebSocket-Accept by using of Sec-WebSocket-Key
     *  @param seckey Sec-WebSocket-Key that receive from client.
     */
    std::string generateAcceptKey(const std::string& seckey);
};

#endif
