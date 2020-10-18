/*!
 * minter_tx.
 * tx_recreate_coin_test.cpp
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_edit_candidate_public_key.h>

TEST(TxEditCandidatePublicKey, TestEncode) {
    const char* expected = "f8951001018014b844f842a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe1808001b845f8431ca0ce7bef38ec15604c100f923c7b0c4c57f18ead5d432cda5ded45cf11d4adbac3a059367227d818d25826df77517f2951001f993f0094072dbe7d9587221e9a7324";
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id(dev::bigint("0"))
                  .set_nonce(dev::bigint("16"))
                  .set_gas_price("1")
                  .set_chain_id(minter::mainnet)
                  .tx_edit_candidate_public_key()
                  ->set_public_key(minter::pubkey_t("Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0"))
                  .set_new_public_key(minter::pubkey_t("Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe1"))
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxEditCandidatePublicKey, TestDecode) {
    const char* encoded = "f8951001018014b844f842a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe1808001b845f8431ca0ce7bef38ec15604c100f923c7b0c4c57f18ead5d432cda5ded45cf11d4adbac3a059367227d818d25826df77517f2951001f993f0094072dbe7d9587221e9a7324";
    auto tx = minter::tx::decode(encoded);
    auto data = tx->get_data<minter::tx_edit_candidate_public_key>();

    ASSERT_EQ(dev::bigint("16"), tx->get_nonce());
    ASSERT_EQ(dev::bigint("0"), tx->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), tx->get_gas_price());
    ASSERT_EQ(minter::mainnet, tx->get_chain_id());
    ASSERT_EQ(minter::signature_type::single, tx->get_signature_type());

    ASSERT_EQ(minter::pubkey_t("Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0"), data->get_public_key());
    ASSERT_EQ(minter::pubkey_t("Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe1"), data->get_new_public_key());
}