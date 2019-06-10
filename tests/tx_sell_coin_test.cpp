/*!
 * minter_tx.
 * tx_sell_coin_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <minter/tx.hpp>
#include <gtest/gtest.h>

TEST(TxSell, TestEncode) {
    const char* expected = "f8830102018a4d4e540000000000000002a9e88a4d4e5400000000000000880de0b6b3a76400008a54455354000000000000880de0b6b3a7640000808001b845f8431ba0e34be907a18acb5a1aed263ef419f32f5adc6e772b92f949906b497bba557df3a0291d7704980994f7a6f5950ca84720746b5928f21c3cfc5a5fbca2a9f4d35db0";
    minter::data::private_key pk = "07bc17abdcee8b971bb8723e36fe9d2523306d5ab2d683631693238e0f9df142";

    auto tx = minter::new_tx()
        ->set_gas_coin("MNT")
        .set_nonce("1")
        .set_gas_price("1")
        .set_chain_id(minter::testnet)
        .tx_sell_coin()
        ->set_coin_to_buy("TEST")
        .set_coin_to_sell("MNT")
        .set_value_to_sell("1")
        .set_min_value_to_buy("1")
        .build();


    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.toHex().c_str());
}

TEST(TxSell, TestDecode) {
    const char* encoded = "f8830102018a4d4e540000000000000002a9e88a4d4e5400000000000000880de0b6b3a76400008a54455354000000000000880de0b6b3a7640000808001b845f8431ba0e34be907a18acb5a1aed263ef419f32f5adc6e772b92f949906b497bba557df3a0291d7704980994f7a6f5950ca84720746b5928f21c3cfc5a5fbca2a9f4d35db0";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_sell_coin>();

    ASSERT_STREQ("TEST", data->get_coin_to_buy().c_str());
    ASSERT_STREQ("MNT", data->get_coin_to_sell().c_str());
    ASSERT_EQ(dev::bigdec18("1"), data->get_value_to_sell());
    ASSERT_EQ(dev::bigdec18("1"), data->get_min_value_to_buy());
}

TEST(TxSellAll, TestEncode) {
    const char* expected = "f87a0102018a4d4e540000000000000003a0df8a4d4e54000000000000008a54455354000000000000880de0b6b3a7640000808001b845f8431ca0b10794a196b6ad2f94e6162613ca9538429dd49ca493594ba9d99f80d2499765a03c1d78e9e04f57336691e8812a16faccb00bf92ac817ab61cd9bf001e9380d47";
    minter::data::private_key pk = "07bc17abdcee8b971bb8723e36fe9d2523306d5ab2d683631693238e0f9df142";

    auto tx = minter::new_tx()
        ->set_gas_coin("MNT")
        .set_nonce("1")
        .set_gas_price("1")
        .set_chain_id(minter::testnet)
        .tx_sell_all_coins()
        ->set_coin_to_buy("TEST")
        .set_coin_to_sell("MNT")
        .set_min_value_to_buy("1")
        .build();


    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.toHex().c_str());
}

TEST(TxSellAll, TestDecode) {
    const char* encoded = "f87a0102018a4d4e540000000000000003a0df8a4d4e54000000000000008a54455354000000000000880de0b6b3a7640000808001b845f8431ca0b10794a196b6ad2f94e6162613ca9538429dd49ca493594ba9d99f80d2499765a03c1d78e9e04f57336691e8812a16faccb00bf92ac817ab61cd9bf001e9380d47";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_sell_all_coins>();

    ASSERT_STREQ("TEST", data->get_coin_to_buy().c_str());
    ASSERT_STREQ("MNT", data->get_coin_to_sell().c_str());
    ASSERT_EQ(dev::bigdec18("1"), data->get_min_value_to_buy());
}
