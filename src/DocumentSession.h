// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_DOCUMENTSESSION_H
#define HTTPLIB_SRC_DOCUMENTSESSION_H

#include <memory>
#include <mutex>
#include <set>
#include <string>

class DocumentManager;
class SocketSession;

/** @brief Manage the operation between SocketSession and DocumentManager. */
class DocumentSession {
private:
    /** @brief Store DocumentManager pointer. It is used to synchronize datas. */
    DocumentManager* doc_manager_;
    /** @brief Store SocketSession object pointer. */
    std::set<SocketSession*> sessions_;
    /** @brief Lock sessions_ when it is used. */
    std::mutex session_mutex_;
    /** @brief Parse update parameter reveived from client message.
     *  @param update_params Client message.
     */
    void parseUpdateParameters(const std::string& update_params);
    /** @brief Syncronize the updates to clients and database. */
    void syncDocument();
public:
    DocumentSession();
    /** @brief Non construction-copyable. */
    DocumentSession(const DocumentSession&) = delete;
    /** @brief Non copyable. */
    DocumentSession &operator=(const DocumentSession&) = delete;
    /** @brief Add session after socket connect.
     *  @param session SocketSession object that will be added to session list.
     */
    void addSession(SocketSession* session);
    /** @brief Remove session after socket close.
     *  @param session SocketSession object that will be removed from session list.
     */
    void removeSession(SocketSession* session);
    /** @brief Update document from client message. Then, function will broadcast to all clients who is editing this document.
     *  @param update_params Client message. The update_params format is like :
     * "{
     *      "index" : int, 
     *      "content" : string
     * }".
     */
    void updateDocument(const std::string &update_params);
};

#endif
