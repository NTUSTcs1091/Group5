// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "DocumentSession.h"

DocumentSession::DocumentSession()
{
    doc_manager_ = new DocumentManager();
}

void DocumentSession::addSession(SocketSession *session, const int id)
{
    sessions_.insert(session);
    std::vector<Revision> *revisions_ = doc_manager_->getHistoryFromDocument(id);
    if (revisions_ != nullptr)
    {
        for (const auto &revision : *revisions_)
        {
            session->sendMessage(SocketUtility::parseMessage(revision.toString()));
        }
    }
}

void DocumentSession::removeSession(SocketSession *session)
{
    sessions_.erase(session);
}

void DocumentSession::parseUpdateParameters(const std::string &update_params)
{
    std::string update_params_ = update_params;
    std::string delimiter = ",";

    size_t pos = 0;
    std::string token;
    std::vector<std::string> param_list;
    while ((pos = update_params_.find(delimiter)) != std::string::npos)
    {
        token = update_params_.substr(0, pos);
        param_list.push_back(token);
        update_params_.erase(0, pos + delimiter.length());
    }
    param_list.push_back(update_params_);
    if (param_list.size() == 7)
    {
        Revision revision(param_list[1], std::stoi(param_list[2]), std::stoi(param_list[3]),
                          param_list[4] == "0" ? false : true, param_list[5], std::stoi(param_list[6]));
        doc_manager_->updateDocumentByID(std::stoi(param_list[0]), revision);
    }
}

void DocumentSession::syncDocument(const std::string &update_params)
{
    for (const auto &session : sessions_)
    {
        session->sendMessage(SocketUtility::parseMessage(update_params));
    }
}

void DocumentSession::updateDocument(const std::string &update_params)
{
    parseUpdateParameters(update_params);
    syncDocument();
}
