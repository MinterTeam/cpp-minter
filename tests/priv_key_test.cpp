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

TEST(PrivateKey, CreateFromMnemonic) {
    const char* expected = "566c043423e08a417aa8b33a7c3253b31f734aecb9ca5485aa08432585164179";
    const char* mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    ASSERT_STREQ(expected, pk.toHex().c_str());
}

TEST(PrivateKey, GetPubKeyUncompressed) {

    const char* expected = "04ffc7249742108c830a9fad45052498698062c8647a3042fab7730dba342ea7cfb4523f0053f8556ba9db39f9c344faa3bf83e949ef20958660c83b93dfa0246d";
    const char* mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    auto pub_key = pk.get_public_key(false);
    ASSERT_EQ(65, pub_key.get().size());

    minter::Data pubkey_data = pub_key.get();

    ASSERT_STREQ(expected, pubkey_data.toHex().c_str());
}

TEST(PrivateKey, GetPubKeyCompressed) {
    const char* expected = "03ffc7249742108c830a9fad45052498698062c8647a3042fab7730dba342ea7cf";
    const char* mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    auto pub_key = pk.get_public_key(true);
    minter::Data pubkey_data = pub_key.get();

    ASSERT_STREQ(expected, pubkey_data.toHex().c_str());
}

TEST(PrivateKey, GetMinterAddress) {
    const char* expected = "42516215b2dd72187d3ef6adb19fc3aabbbced23";

    const char* mnem = "original expand list pencil blade ivory express achieve inside stool apple truck";
    minter::privkey_t pk = minter::privkey_t::from_mnemonic(mnem);

    minter::address_t address(pk);

    ASSERT_STREQ(expected, address.to_string_no_prefix().c_str());
    std::cout << "Address: " << address.to_string() << std::endl;
}