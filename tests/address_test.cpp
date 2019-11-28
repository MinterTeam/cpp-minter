/*!
 * minter_tx.
 * address_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <sstream>
#include <gtest/gtest.h>
#include <minter/address.h>
#include <minter/private_key.h>

static const char *NULL_ADDRESS_NO_PREFIX = "0000000000000000000000000000000000000000";
static const char *NULL_ADDRESS = "Mx0000000000000000000000000000000000000000";
static const char *TEST_ADDRESS_NO_PREFIX = "42516215b2dd72187d3ef6adb19fc3aabbbced23";
static const char *TEST_ADDRESS = "Mx42516215b2dd72187d3ef6adb19fc3aabbbced23";
static const uint8_t TEST_ADDRESS_DATA[] = {
    0x42, 0x51, 0x62, 0x15,
    0xb2, 0xdd, 0x72, 0x18,
    0x7d, 0x3e, 0xf6, 0xad,
    0xb1, 0x9f, 0xc3, 0xaa,
    0xbb, 0xbc, 0xed, 0x23
};
static const std::vector<uint8_t> TEST_ADDRESS_VECT = {
    0x42, 0x51, 0x62, 0x15,
    0xb2, 0xdd, 0x72, 0x18,
    0x7d, 0x3e, 0xf6, 0xad,
    0xb1, 0x9f, 0xc3, 0xaa,
    0xbb, 0xbc, 0xed, 0x23
};


TEST(Address, DefaultCtr) {
    minter::address_t address;
    ASSERT_STREQ(NULL_ADDRESS, address.to_string().c_str());
    ASSERT_STREQ(NULL_ADDRESS_NO_PREFIX, address.to_string_no_prefix().c_str());

    address = TEST_ADDRESS;
    ASSERT_STREQ(TEST_ADDRESS, address.to_string().c_str());
    ASSERT_STREQ(TEST_ADDRESS_NO_PREFIX, address.to_string_no_prefix().c_str());
}

TEST(Address, StringCtr) {
    minter::address_t a(TEST_ADDRESS);
    ASSERT_STREQ(TEST_ADDRESS, a.to_string().c_str());

    std::string bs = TEST_ADDRESS;
    minter::address_t b(bs);

    std::string cs = TEST_ADDRESS + 2;
    minter::address_t c(cs);

    ASSERT_STREQ(TEST_ADDRESS, b.to_string().c_str());
    ASSERT_STREQ(TEST_ADDRESS, c.to_string().c_str());

    bool threw = false;
    std::string errmsg;
    try {
        minter::address_t d("wtf");
    } catch (const std::runtime_error &e) {
        // length is not 40 or 42
        errmsg = e.what();
        threw = true;
    } catch (const std::exception &e) {
        errmsg = e.what();
    }

    ASSERT_STREQ("address length is not valid", errmsg.c_str());
    ASSERT_TRUE(threw);

    threw = false;
    errmsg = "";

    try {
        minter::address_t d(std::string("some invalid hex string"));
    } catch (const std::runtime_error &e) {
        // length is not 40 or 42
        errmsg = e.what();
        threw = true;
    }
    ASSERT_STREQ("address length is not valid", errmsg.c_str());
    ASSERT_TRUE(threw);
}

TEST(Address, PtrCtor) {
    minter::address_t a(TEST_ADDRESS);
    minter::address_t b(a.get());

    ASSERT_EQ(a, b);
    ASSERT_TRUE(a == b);

    minter::address_t c(a.data(), 20);
    ASSERT_EQ(a, c);
    ASSERT_TRUE(a == c);

    // implicit constructor
    minter::address_t d = a.get();
    ASSERT_EQ(a, d);
    ASSERT_TRUE(a == d);
}

TEST(Address, Equaling) {
    minter::address_t a;
    minter::address_t b(TEST_ADDRESS);
    minter::address_t c(TEST_ADDRESS);

    ASSERT_NE(a, b);
    ASSERT_FALSE(a == b);
    ASSERT_EQ(b, c);
    ASSERT_TRUE(b == c);
}

TEST(Address, ToString) {
    minter::address_t a(TEST_ADDRESS);
    std::string address = (std::string) a;

    ASSERT_STREQ(TEST_ADDRESS, address.c_str());
}

TEST(Address, StreamWrite) {
    minter::address_t a(TEST_ADDRESS);
    std::stringstream ss;
    ss << a;

    std::string sr = ss.str();
    ASSERT_STREQ(TEST_ADDRESS, sr.c_str());
}