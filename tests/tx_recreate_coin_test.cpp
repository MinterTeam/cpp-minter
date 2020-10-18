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
#include <minter/tx/tx_recreate_coin.h>

TEST(TxRecreateCoin, TestEncode) {
    const char* expected = "f8985a02018010b847f8459342616e616e61205465737420436f696e2056328a42414e414e41544553548a152d02c7e14af68000008a152d02c7e14af6800000508e314dc6448d9338c15b0a00000000808001b845f8431ca03a0a522a72f5301fec4f63df67f8718d69cd44f5cf6090fd0a394b13a82b942da0492f6f90e2609dc487f2fb265d17c03894e831f0bffe46659ae1828f099610c1";
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id(dev::bigint("0"))
                  .set_nonce(dev::bigint("90"))
                  .set_gas_price("1")
                  .set_chain_id(minter::testnet)
                  .tx_recreate_coin()
                  ->set_name("Banana Test Coin V2")
                  .set_ticker("BANANATEST")
                  .set_initial_amount("100000")
                  .set_initial_reserve("100000")
                  .set_max_supply("1000000000000000")
                  .set_crr(80)
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxRecreateCoin, TestDecode) {
    const char* encoded = "f8985a02018010b847f8459342616e616e61205465737420436f696e2056328a42414e414e41544553548a152d02c7e14af68000008a152d02c7e14af6800000508e314dc6448d9338c15b0a00000000808001b845f8431ca03a0a522a72f5301fec4f63df67f8718d69cd44f5cf6090fd0a394b13a82b942da0492f6f90e2609dc487f2fb265d17c03894e831f0bffe46659ae1828f099610c1";
    auto tx = minter::tx::decode(encoded);
    auto data = tx->get_data<minter::tx_create_coin>();

    ASSERT_EQ(dev::bigint("90"), tx->get_nonce());
    ASSERT_EQ(dev::bigint("0"), tx->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), tx->get_gas_price());
    ASSERT_EQ(minter::testnet, tx->get_chain_id());

    ASSERT_STREQ("Banana Test Coin V2", data->get_name().c_str());
    ASSERT_STREQ("BANANATEST", data->get_ticker().c_str());
    ASSERT_EQ(dev::bigdec18("100000"), data->get_initial_amount());
    ASSERT_EQ(dev::bigdec18("100000"), data->get_initial_reserve());
    ASSERT_EQ((uint32_t) 80, data->get_crr());
    ASSERT_EQ(dev::bigdec18("1000000000000000"), data->get_max_supply());
    ASSERT_EQ(minter::signature_type::single, tx->get_signature_type());
}