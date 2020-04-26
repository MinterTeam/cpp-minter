/*!
 * minter_tx.
 * tx_create_coin_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_create_coin.h>

TEST(TxCreateCoin, TestEncode) {
    const char* expected = "f88f0102018a4d4e540000000000000005b5f48a535550455220544553548a5350525445535400000089056bc75e2d63100000888ac7230489e800000a893635c9adc5dea00000808001b845f8431ca0ccfabd9283d27cf7978bca378e0cc7dc69a39ff3bdc56707fa2d552655f9290da0226057221cbaef35696c9315cd29e783d3c66d842d0a3948a922abb42ca0dabe";
    minter::privkey_t pk = "07bc17abdcee8b971bb8723e36fe9d2523306d5ab2d683631693238e0f9df142";

    auto tx = minter::new_tx()
                  ->set_gas_coin("MNT")
                  .set_nonce("1")
                  .set_gas_price("1")
                  .set_chain_id(minter::testnet)
                  .tx_create_coin()
                  ->set_name("SUPER TEST")
                  .set_ticker("SPRTEST")
                  .set_initial_amount("100")
                  .set_initial_reserve("10")
                  .set_max_supply("1000")
                  .set_crr(10)
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxCreateCoin, TestDecode) {
    const char* encoded = "f88f0102018a4d4e540000000000000005b5f48a535550455220544553548a5350525445535400000089056bc75e2d63100000888ac7230489e800000a893635c9adc5dea00000808001b845f8431ca0ccfabd9283d27cf7978bca378e0cc7dc69a39ff3bdc56707fa2d552655f9290da0226057221cbaef35696c9315cd29e783d3c66d842d0a3948a922abb42ca0dabe";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_create_coin>();

    ASSERT_STREQ("SPRTEST", data->get_ticker().c_str());
    ASSERT_STREQ("SUPER TEST", data->get_name().c_str());
    ASSERT_EQ(dev::bigdec18("100"), data->get_initial_amount());
    ASSERT_EQ(dev::bigdec18("10"), data->get_initial_reserve());
    ASSERT_EQ((uint32_t) 10, data->get_crr());
    ASSERT_EQ(dev::bigdec18("1000"), data->get_max_supply());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
}