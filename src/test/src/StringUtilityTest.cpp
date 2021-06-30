#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "StringUtility.h"

TEST(splitTest, Split) {
	std::vector<std::string> x = StringUtility::split("Test String Split with Space Delimiter.", " ");
	std::vector<std::string> y = { "Test", "String", "Split", "with", "Space", "Delimiter." };
	ASSERT_EQ(x.size(), y.size());
	for (int i = 0; i < x.size(); i++) {
		EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
	}
}

TEST(sha1Test, SHA1) {
	std::stringstream ss;
	std::string src = StringUtility::sha1("I am string.");
	std::string y = "5bdf667b1dfbf56cdaeeb9aff97cb3c95deb3241";
	for (int i = 0; i < src.length(); i++) {
		int tmp = int(src[i]);
		ss << std::hex << ((tmp & 0xF0) >> 4);
		ss << std::hex << (tmp & 0x0F);
	}
	std::string x = ss.str();
	EXPECT_EQ(0, strcmp(x.c_str(), y.c_str()));
}

TEST(encodeBase64Test, EncodeBase64) {
	std::string x = StringUtility::encodeBase64("I am string.");
	std::string y = "SSBhbSBzdHJpbmcu";
	EXPECT_EQ(0, strcmp(x.c_str(), y.c_str()));
}
