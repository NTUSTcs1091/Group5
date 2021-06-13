// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTTPLIB_SRC_STRINGUTILITY_H
#define HTTPLIB_SRC_STRINGUTILITY_H

#include <vector>
#include <string>

/** @brief String utility function */
namespace StringUtility {
    /** @brief Split input string into tokens by use of delimiters.
     *
     *  This method is equivalent to:
     *      std::vector<std::string> token(0);
     *      boost::split(token, str, boost::is_any_of(dels), boost::token_compress_on);
     *      return token;
     *
     *  @param str Input string.
     *  @param dels Characters that seperate string.
     *  @return Result tokens.
     */
    std::vector<std::string> split(const std::string& str, const std::string& dels);
    /** @brief Generate sha1 hash of the string.
     *  @param str Input string.
     *  @return sha1 hash of input string.
     */
    std::string sha1(const std::string& str);
    /** @brief Encode string into Base64.
     *  @param str Input string.
     *  @return Base64 string.
     */
    std::string encodeBase64(const std::string& str);
};

#endif
