// Copyright (c) 2021, Kung-Yao Hsieh, Shang-Chen LIN, Yi-Hang Xie. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "StringUtility.h"

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

namespace StringUtility {
    std::vector<std::string> split(const std::string& str, const std::string& dels) {
        std::vector<std::string> token(0);
        // token_compress_on means that function will reduce the empty string.
        boost::split(token, str, boost::is_any_of(dels), boost::token_compress_on);
        return token;
    }

    std::string sha1(const std::string& str) {
        const EVP_MD* md = EVP_sha1();
        EVP_MD_CTX* mdctx = EVP_MD_CTX_create();
        unsigned int output_length = 0;
        unsigned char output_buf[EVP_MAX_MD_SIZE];

        EVP_DigestInit_ex(mdctx, md, NULL);
        EVP_DigestUpdate(mdctx, str.c_str(), str.length());
        EVP_DigestFinal_ex(mdctx, output_buf, &output_length);
        EVP_MD_CTX_destroy(mdctx);
        EVP_cleanup();

        std::string result((char *)output_buf, output_length);
        return result;
    }

    // https://gist.github.com/barrysteyn/7308212
    std::string encodeBase64(const std::string& str) {
        BIO* bmem = NULL;
        BIO* b64 = NULL;
        BUF_MEM* bptr = NULL;

        b64 = BIO_new(BIO_f_base64());
        //Ignore newlines
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        bmem = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, bmem);
        BIO_write(b64, str.c_str(), str.length());
        BIO_flush(b64);
        BIO_get_mem_ptr(b64, &bptr);

        std::string result(bptr->data, bptr->length);
        // According to OpenSSl API document, we do not need to free *bmem because
        // this function will free entire BIO chain. 
        BIO_free_all(b64);

        return result;
    }
}
