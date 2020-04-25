/*!
 * minter_tx.
 * utils_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx/utils.h>

TEST(Utils, TestToBytesMNTCCharFixed) {
    const char* c1 = "MNT";
    auto res = minter::utils::to_bytes_fixed(c1, 10);

    ASSERT_EQ(10, res.size());
    ASSERT_EQ('M', res[0]);
    ASSERT_EQ('N', res[1]);
    ASSERT_EQ('T', res[2]);
    ASSERT_EQ((uint8_t) 0x00, res[3]);
    ASSERT_EQ((uint8_t) 0x00, res[9]);
}

TEST(Utils, TestToBytesMNTStringFixed) {
    const std::string c1 = "MNT";
    auto res = minter::utils::to_bytes_fixed(c1, 10);

    ASSERT_EQ(10, res.size());
    ASSERT_EQ('M', res[0]);
    ASSERT_EQ('N', res[1]);
    ASSERT_EQ('T', res[2]);
    ASSERT_EQ((uint8_t) 0x00, res[3]);
    ASSERT_EQ((uint8_t) 0x00, res[9]);
}

TEST(Utils, TestToBytesSPRTESTStringFixed) {
    const std::string c1 = "SPRTEST";
    auto res = minter::utils::to_bytes_fixed(c1, 10);

    ASSERT_EQ(10, res.size());
    ASSERT_EQ('S', res[0]);
    ASSERT_EQ('P', res[1]);
    ASSERT_EQ('R', res[2]);
    ASSERT_EQ('T', res[3]);
    ASSERT_EQ('E', res[4]);
    ASSERT_EQ('S', res[5]);
    ASSERT_EQ('T', res[6]);
    ASSERT_EQ((uint8_t) 0x00, res[7]);
    ASSERT_EQ((uint8_t) 0x00, res[9]);
}

TEST(Utils, SHA256) {
    const char* expected = "61d034473102d7dac305902770471fd50f4c5b26f6831a56dd90b5184b3c30fc";
    dev::bytes_data exp_data(expected);
    const std::string val = "some string";
    dev::bytes_data res = minter::utils::sha256(std::vector<uint8_t>(val.begin(), val.end()));

    ASSERT_STREQ(expected, res.to_hex().c_str());
    ASSERT_EQ(exp_data, res);
    ASSERT_TRUE(exp_data == res);
}

TEST(Utils, Base64Web1) {
    const std::string test = "hello";
    const std::string result = "aGVsbG8";
    dev::bytes_data encoded = dev::bytes_data::from_string_raw(test);
    encoded.switch_map(minter::utils::to_base64_web);
    ASSERT_STREQ(result.c_str(), encoded.to_string().c_str());

    dev::bytes_data decoded = encoded.switch_map_c(minter::utils::from_base64_web);
    ASSERT_STREQ(test.c_str(), decoded.to_string().c_str());
}

TEST(Utils, Base64Web2) {
    const std::string test = "hellow";
    const std::string result = "aGVsbG93";
    dev::bytes_data encoded = dev::bytes_data::from_string_raw(test);
    encoded.switch_map(minter::utils::to_base64_web);
    ASSERT_STREQ(result.c_str(), encoded.to_string().c_str());

    dev::bytes_data decoded = encoded.switch_map_c(minter::utils::from_base64_web);
    ASSERT_STREQ(test.c_str(), decoded.to_string().c_str());
}

TEST(Utils, Base64Web3) {
    const std::string test = "hellowo";
    const std::string result = "aGVsbG93bw";
    dev::bytes_data encoded = dev::bytes_data::from_string_raw(test);
    encoded.switch_map(minter::utils::to_base64_web);
    ASSERT_STREQ(result.c_str(), encoded.to_string().c_str());

    dev::bytes_data decoded = encoded.switch_map_c(minter::utils::from_base64_web);
    ASSERT_STREQ(test.c_str(), decoded.to_string().c_str());
}

TEST(Utils, Base64Web4) {
    const std::string test = "hellowor";
    const std::string result = "aGVsbG93b3I";
    dev::bytes_data encoded = dev::bytes_data::from_string_raw(test);
    encoded.switch_map(minter::utils::to_base64_web);
    ASSERT_STREQ(result.c_str(), encoded.to_string().c_str());

    dev::bytes_data decoded = encoded.switch_map_c(minter::utils::from_base64_web);
    ASSERT_STREQ(test.c_str(), decoded.to_string().c_str());
}

TEST(Utils, Base64Web5) {
    const std::string test = "helloworl";
    const std::string result = "aGVsbG93b3Js";
    dev::bytes_data encoded = dev::bytes_data::from_string_raw(test);
    encoded.switch_map(minter::utils::to_base64_web);
    ASSERT_STREQ(result.c_str(), encoded.to_string().c_str());

    dev::bytes_data decoded = encoded.switch_map_c(minter::utils::from_base64_web);
    ASSERT_STREQ(test.c_str(), decoded.to_string().c_str());
}

TEST(Utils, Base64Web6) {
    const std::string test = "helloworld";
    const std::string result = "aGVsbG93b3JsZA";
    dev::bytes_data encoded = dev::bytes_data::from_string_raw(test);
    encoded.switch_map(minter::utils::to_base64_web);
    ASSERT_STREQ(result.c_str(), encoded.to_string().c_str());

    dev::bytes_data decoded = encoded.switch_map_c(minter::utils::from_base64_web);
    ASSERT_STREQ(test.c_str(), decoded.to_string().c_str());
}