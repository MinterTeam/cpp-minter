/*!
 * minter_tx.
 * tx_declare_candidacy_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_multisend.h>

TEST(TxMultisend, TestEncode) {
    const char* expected =
        "f895060101800db844f842f840df809467691076548b20234461ff6fd2bc9c64393eb8fc8801b4fbd92b5f8000df8094d82558ea00eb81d35f2654953598f5d51737d31d8804746bcc9ce68000808001b845f8431ba0a936ac922d8d67f06efc996f50f3d2af55a77453f521bc96d73158de16b530baa0192f5d1f2feb520b38d92513ed89fc1ede26353ce3660502f61721ea6232b261";

    minter::privkey_t priv_key = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id("0")
                  .set_nonce("6")
                  .set_gas_price("1")
                  .set_chain_id(minter::mainnet)
                  .tx_multisend()
                  ->add_item(dev::bigint("0"), "Mx67691076548b20234461ff6fd2bc9c64393eb8fc", "0.123")
                  .add_item(dev::bigint("0"), "Mxd82558ea00eb81d35f2654953598f5d51737d31d", "0.321")
                  .build();

    auto signature = tx->sign_single(priv_key);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxMultisend, TestDecode) {
    const char* encoded =
        "f895060101800db844f842f840df809467691076548b20234461ff6fd2bc9c64393eb8fc8801b4fbd92b5f8000df8094d82558ea00eb81d35f2654953598f5d51737d31d8804746bcc9ce68000808001b845f8431ba0a936ac922d8d67f06efc996f50f3d2af55a77453f521bc96d73158de16b530baa0192f5d1f2feb520b38d92513ed89fc1ede26353ce3660502f61721ea6232b261";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_multisend>();

    ASSERT_EQ(2, data->get_items().size());
    minter::send_target t1 = data->get_items()[0];
    minter::send_target t2 = data->get_items()[1];

    ASSERT_STREQ("Mx67691076548b20234461ff6fd2bc9c64393eb8fc", t1.to.to_string().c_str());
    ASSERT_STREQ("Mxd82558ea00eb81d35f2654953598f5d51737d31d", t2.to.to_string().c_str());
    ASSERT_EQ(dev::bigdec18("0.123"), t1.get_amount());
    ASSERT_EQ(dev::bigdec18("0.321"), t2.get_amount());
    ASSERT_EQ(minter::def_coin_id, t1.coin_id);
    ASSERT_EQ(minter::def_coin_id, t2.coin_id);
}