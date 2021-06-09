// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "SocketUtility.h"
#include "StringUtility.h"


SocketUtility::WSMessage parseMessage(const std::string& message) {
        return SocketUtility::WSMessage{};
}

std::string SocketUtility::generateAcceptKey(const std::string& seckey) {
	return StringUtility::encodeBase64(
	StringUtility::sha1(seckey + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11")
	);
}

SocketUtility::Frame SocketUtility::DecodeMessage(const std::string & buffer){
	SocketUtility::Frame wsFrame;
	int pos = 0;
	wsFrame.fin = (uint8_t)((buffer[pos] >> 7) & 0x1);
	wsFrame.opcode = (uint8_t)(buffer[pos] & 0xf);
	pos++;
	wsFrame.Mask = (uint8_t)((buffer[pos] >> 7) & 0x1);
	wsFrame.PayloadLen = (uint8_t)(buffer[pos] & 0x7f);
	pos++;

	if (wsFrame.opcode == 0x1) {
		if (wsFrame.PayloadLen == 126) {
			memcpy(&wsFrame.PayloadLen, &buffer[0] + pos, 2);
			wsFrame.PayloadLen = ntohs(wsFrame.PayloadLen);
			pos += 2;
		}
		else if (wsFrame.PayloadLen == 127) {
			memcpy(&wsFrame.PayloadLen, &buffer[0] + pos, 8);
			wsFrame.PayloadLen = ntohl(wsFrame.PayloadLen);
			pos += 8;
		}
		wsFrame.Payload = new char[wsFrame.PayloadLen + 1];

		if (wsFrame.Mask == 1) {
			memcpy(wsFrame.Maskingkey, &buffer[0] + pos, 4);
			pos += 4;

			for (int i = 0; i < wsFrame.PayloadLen; i++) {
				int j = i % 4;
				wsFrame.Payload[i] = buffer[pos + i] ^ wsFrame.Maskingkey[j];
			}
		}
		else {
			memcpy(wsFrame.Payload, &buffer[0] + pos, wsFrame.PayloadLen);
		}
		wsFrame.Payload[wsFrame.PayloadLen] = '\0';
	}
	return wsFrame;
}

std::string SocketUtility::EncodeMessage(const SocketUtility::Frame & frame){
	std::string sendedMSG = "";

	char code1 = (frame.fin << 7) | frame.opcode;
	char code2 = (frame.Mask << 7) | frame.PayloadLen;

	sendedMSG.append(1, code1);
	sendedMSG.append(1, code2);

	for (int i = 0; i < frame.PayloadLen; i++) {
		int j = i % 4;
		sendedMSG.append(1, frame.Payload[i]);
	}
	return sendedMSG;
}

