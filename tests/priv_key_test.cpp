/*!
 * minter_tx.
 * priv_key_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */


#include <gtest/gtest.h>
#include <minter/private_key.h>
#include <minter/address.h>
#include <sstream>

static const char *NULL_PRIVKEY = "0000000000000000000000000000000000000000000000000000000000000000";
static const char *TEST_PRIVKEY = "566c043423e08a417aa8b33a7c3253b31f734aecb9ca5485aa08432585164179";
static const char *TEST_PRIVKEY20 = "566c043423e08a417aa8b33a7c3253b31f734aec000000000000000000000000";

TEST(PrivateKey, StreamWrite) {
    std::stringstream ss;
    minter::privkey_t pk(TEST_PRIVKEY);
    ss << pk;

    std::string res = ss.str();

    ASSERT_STREQ(TEST_PRIVKEY, res.c_str());

}

TEST(PrivateKey, CreateFromMnemonic) {
    const char *expected = "566c043423e08a417aa8b33a7c3253b31f734aecb9ca5485aa08432585164179";
    const char *mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    ASSERT_STREQ(expected, pk.to_hex().c_str());
}

TEST(PrivateKey, EmptyCtor) {
    minter::privkey_t a;
    ASSERT_STREQ(NULL_PRIVKEY, a.to_string().c_str());
}

TEST(PrivKey, Equaling) {
    minter::privkey_t a = TEST_PRIVKEY;
    minter::privkey_t b = std::string(TEST_PRIVKEY);

    ASSERT_EQ(a, b);
    ASSERT_TRUE(a == b);

    minter::privkey_t c;
    ASSERT_NE(a, c);
    ASSERT_TRUE(a != c);

    std::string pk = (std::string) a;
    ASSERT_STREQ(TEST_PRIVKEY, pk.c_str());

    a.clear();
    ASSERT_STREQ(NULL_PRIVKEY, a.to_string().c_str());
}

TEST(PrivKey, DataCtr) {
    uint8_t data[32];
    auto vecdata = toolboxpp::data::hexToBytes(TEST_PRIVKEY);
    memcpy(data, vecdata.data(), 32);
    minter::privkey_t a(data);
    ASSERT_STREQ(TEST_PRIVKEY, a.to_string().c_str());

    minter::privkey_t b(data, 32);
    ASSERT_STREQ(TEST_PRIVKEY, b.to_string().c_str());

    minter::privkey_t b2(data, 20);
    ASSERT_STRNE(TEST_PRIVKEY, b2.to_string().c_str());
    ASSERT_STREQ(TEST_PRIVKEY20, b2.to_string().c_str());

    minter::privkey_t c(vecdata);
    ASSERT_STREQ(TEST_PRIVKEY, c.to_string().c_str());

    minter::privkey_t d(std::move(vecdata));
    ASSERT_STREQ(TEST_PRIVKEY, d.to_string().c_str());
}

TEST(PrivateKey, FromMnemonicString) {

    const char *expected =
        "04ffc7249742108c830a9fad45052498698062c8647a3042fab7730dba342ea7cfb4523f0053f8556ba9db39f9c344faa3bf83e949ef20958660c83b93dfa0246d";
    const std::string mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    auto pub_key = pk.get_public_key(false);
    ASSERT_EQ(65, pub_key.get().size());

    minter::Data pubkey_data = pub_key.get();

    ASSERT_STREQ(expected, pubkey_data.to_hex().c_str());

    std::cout << pk.to_string() << std::endl;
}

TEST(PrivateKey, GetPubKeyUncompressed) {

    const char *expected =
        "04ffc7249742108c830a9fad45052498698062c8647a3042fab7730dba342ea7cfb4523f0053f8556ba9db39f9c344faa3bf83e949ef20958660c83b93dfa0246d";
    const char *mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    auto pub_key = pk.get_public_key(false);
    ASSERT_EQ(65, pub_key.get().size());

    minter::Data pubkey_data = pub_key.get();

    ASSERT_STREQ(expected, pubkey_data.to_hex().c_str());
}

TEST(PrivateKey, GetPubKeyCompressed) {
    const char *expected = "03ffc7249742108c830a9fad45052498698062c8647a3042fab7730dba342ea7cf";
    const char *mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    auto pub_key = pk.get_public_key(true);
    minter::Data pubkey_data = pub_key.get();

    ASSERT_STREQ(expected, pubkey_data.to_hex().c_str());
}

TEST(PrivateKey, GetMinterAddress) {
    const char *expected = "42516215b2dd72187d3ef6adb19fc3aabbbced23";

    const char *mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    minter::address_t address(pk);

    ASSERT_STREQ(expected, address.to_string_no_prefix().c_str());
    std::cout << "Address: " << address.to_string() << std::endl;
}