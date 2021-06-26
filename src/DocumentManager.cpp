// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "DocumentManager.h"

void DocumentManager::updateDocumentByID(const int id, Revision revision)
{
    if (doc_map.find(id) != doc_map.end())
    {
        doc_map.find(id)->second.history.push_back(revision);
    }
    else
    {
        Document doc(id, std::vector<Revision>());
        doc_map.insert(std::pair<int, Revision>(id, doc));
    }
}

std::vector<Revision> *DocumentManager::getHistoryFromDocument(const int id)
{
    if (doc_map.find(id) != doc_map.end())
    {
        return &doc_map.find(id)->second.history;
    }
    else
    {
        return nullptr;
    }
}