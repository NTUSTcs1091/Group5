// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_DOCUMENTMANAGER_H
#define HTTPLIB_SRC_DOCUMENTMANAGER_H

#include <string>
#include <vector>

#include "DocumentSession.h"

class DocumentSession;

/** @brief Store document modify revision */
typedef struct
{
    /** @brief Constructor for Vector Initializing. */
    Revision(std::string user_id_, int start_position_, int end_position_, bool is_insert_, std::string insert_data_, int delete_length_)
        : user_id(user_id_), start_position(start_position_), end_position(end_position_), is_insert(is_insert_), insert_data(insert_data_), delete_length(delete_length_);
    /** @brief Who made this revision. */
    std::string user_id;
    /** @brief Relative insert position from document start and end. */
    int start_position;
    int end_position;
    /** @brief If true,this revision inserts text.If false,this revision deletes text. */
    bool is_insert;
    /** @brief insertData and deleteLength will only exist one at the same time. */
    std::string insert_data;
    int delete_length;
} Revision;

typedef struct
{
    /** @brief Document id. */
    int id;
    /** @brief Modify history list. */
    std::vector<Revision> history;
} Document;

/** @brief Document Manager */
class DocumentManager
{
private:
    /** @brief Map recording id and DocumentSession. */
    std::map<int, DocumentSession *> doc_map;

public:
    DocumentManager();

    /** @brief Non construction-copyable. */
    DocumentManager(const DocumentManager &) = delete;

    /** @brief Non copyable. */
    DocumentManager &operator=(const DocumentManager &) = delete;

    /** @brief Retrive Document Session from id
     * @param message document id.
    */
    DocumentSession *getDocumentFromID(int id);

    /** @brief Load dormanted document from disk.
     * @param message document id.
    */
    bool loadDocument(int id);

    /** @brief Save unused document to disk and release.
     * @param message document id.
    */
    bool saveDocument(int id);

    /** @brief Initialize function to create docMap_. */
    bool createDocumentMap();
};

#endif
