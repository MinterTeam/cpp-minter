/*!
 * minter_tx.
 * utils_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <minter/tx/utils.h>
#include <gtest/gtest.h>

TEST(Utils, TestToBytesMNTCCharFixed) {
    const char* c1 = "MNT";
    auto res = minter::utils::to_bytes_fixed(c1, 10);

    ASSERT_EQ(10, res.size());
    ASSERT_EQ('M', res[0]);
    ASSERT_EQ('N', res[1]);
    ASSERT_EQ('T', res[2]);
    ASSERT_EQ((uint8_t)0x00, res[3]);
    ASSERT_EQ((uint8_t)0x00, res[9]);
}

TEST(Utils, TestToBytesMNTStringFixed) {
    const std::string c1 = "MNT";
    auto res = minter::utils::to_bytes_fixed(c1, 10);

    ASSERT_EQ(10, res.size());
    ASSERT_EQ('M', res[0]);
    ASSERT_EQ('N', res[1]);
    ASSERT_EQ('T', res[2]);
    ASSERT_EQ((uint8_t)0x00, res[3]);
    ASSERT_EQ((uint8_t)0x00, res[9]);
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
    ASSERT_EQ((uint8_t)0x00, res[7]);
    ASSERT_EQ((uint8_t)0x00, res[9]);
}

 