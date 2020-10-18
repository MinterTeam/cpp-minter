/*!
 * minter_tx.
 * tx_set_candidate_on_off
 *
 * \date 27.04.19
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_set_candidate_on_off.h>

TEST(TxSetCandidateOn, TestEncode) {
    const char* expected = "f8720d0101800aa2e1a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0808001b845f8431ca081ebbc4770e7d9d6236614794d5749ab5a925c5f733bae5a34fa525f840157fba043970f8e6bcaf6a7ba2d6895b0c9e99da404ebfa77899d28e05e6ca91f0a092f";
    minter::pubkey_t pubkey = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0";
    minter::privkey_t privkey = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_nonce("13")
                  .set_gas_coin_id("0")
                  .set_chain_id(minter::chain_id::mainnet)
                  .tx_set_candidate_on()
                  ->set_pub_key(pubkey)
                  .build();

    auto signature = tx->sign_single(privkey);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxSetCandidateOn, TestDecode) {
    const char* encoded = "f8720d0101800aa2e1a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0808001b845f8431ca081ebbc4770e7d9d6236614794d5749ab5a925c5f733bae5a34fa525f840157fba043970f8e6bcaf6a7ba2d6895b0c9e99da404ebfa77899d28e05e6ca91f0a092f";
    minter::pubkey_t pubkey = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0";

    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_set_candidate_on>();
    ASSERT_EQ(pubkey, data->get_pub_key());
    ASSERT_EQ(dev::bigint("13"), decoded->get_nonce());
    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
}

TEST(TxSetCandidateOff, TestEncode) {
    const char* expected = "f8720e0101800ba2e1a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0808001b845f8431ba024c5fc033d9d6ad2bfecb37680db84a897839813fd0ad5583254b69180954fb9a022728b74156536acc44c3ef572cc20947a1a015c94b13e36068e1089c95d025b";
    minter::privkey_t privkey = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";
    minter::pubkey_t pubkey = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0";

    auto tx = minter::new_tx()
                  ->set_nonce("14")
                  .set_gas_coin_id("0")
                  .set_chain_id(minter::chain_id::mainnet)
                  .tx_set_candidate_off()
                  ->set_pub_key(pubkey)
                  .build();

    auto signature = tx->sign_single(privkey);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxSetCandidateOff, TestDecode) {
    const char* encoded = "f8720e0101800ba2e1a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0808001b845f8431ba024c5fc033d9d6ad2bfecb37680db84a897839813fd0ad5583254b69180954fb9a022728b74156536acc44c3ef572cc20947a1a015c94b13e36068e1089c95d025b";
    minter::pubkey_t pubkey = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0";

    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_set_candidate_off>();
    ASSERT_EQ(pubkey, data->get_pub_key());
    ASSERT_EQ(dev::bigint("14"), decoded->get_nonce());
    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
}