/*!
 * minter_tx.
 * tx_declare_candidacy_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx/tx_builder.h>
#include <minter/tx/tx_edit_candidate.h>

TEST(TxEditCandidate, TestEncode) {
    const char* expected =
        "f8a80102018a4d4e54000000000000000eb84df84ba00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a439442516215b2dd72187d3ef6adb19fc3aabbbced239442516215b2dd72187d3ef6adb19fc3aabbbced23808001b845f8431ba005b789fdca2d6a08ae47d62d60cfd442aad3eb7ed110373aba348ec687c15a28a035a7f223ab8d2675419f036445aac07b537882b1f3e10dd9e4d06cdb5ac44a38";

    minter::privkey_t priv_key = minter::privkey_t::from_mnemonic(
        "original expand list pencil blade ivory express achieve inside stool apple truck");
    minter::address_t address(priv_key);
    minter::pubkey_t pub_key = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";

    auto tx = minter::new_tx()
                  ->set_gas_coin("MNT")
                  .set_nonce("1")
                  .set_gas_price("1")
                  .set_chain_id(minter::testnet)
                  .tx_edit_candidate()
                  ->set_pub_key(pub_key)
                  .set_reward_address(address)
                  .set_owner_address(address)
                  .build();

    auto signature = tx->sign_single(priv_key);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxEditCandidate, TestDecode) {
    const char* encoded =
        "f8a80102018a4d4e54000000000000000eb84df84ba00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a439442516215b2dd72187d3ef6adb19fc3aabbbced239442516215b2dd72187d3ef6adb19fc3aabbbced23808001b845f8431ba005b789fdca2d6a08ae47d62d60cfd442aad3eb7ed110373aba348ec687c15a28a035a7f223ab8d2675419f036445aac07b537882b1f3e10dd9e4d06cdb5ac44a38";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_edit_candidate>();

    minter::privkey_t priv_key = minter::privkey_t::from_mnemonic(
        "original expand list pencil blade ivory express achieve inside stool apple truck");
    minter::address_t address(priv_key);
    minter::pubkey_t pub_key = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";

    ASSERT_EQ(pub_key, data->get_pub_key());
    ASSERT_EQ(address, data->get_reward_address());
    ASSERT_EQ(address, data->get_owner_address());
}