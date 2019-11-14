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

TEST(TxMultisend, TestEncode) {
    const char *expected =
        "f8b30102018a4d4e54000000000000000db858f856f854e98a4d4e540000000000000094fe60014a6e9ac91618f5d1cab3fd58cded61ee9988016345785d8a0000e98a4d4e540000000000000094ddab6281766ad86497741ff91b6b48fe85012e3c8802c68af0bb140000808001b845f8431ca0b15dcf2e013df1a2aea02e36a17af266d8ee129cdcb3e881d15b70c9457e7571a0226af7bdaca9d42d6774c100b22e0c7ba4ec8dd664d17986318e905613013283";

    minter::privkey_t priv_key = "07bc17abdcee8b971bb8723e36fe9d2523306d5ab2d683631693238e0f9df142";

    auto tx = minter::new_tx()
        ->set_gas_coin("MNT")
        .set_nonce("1")
        .set_gas_price("1")
        .set_chain_id(minter::testnet)
        .tx_multisend()
        ->add_item("MNT", "Mxfe60014a6e9ac91618f5d1cab3fd58cded61ee99", "0.1")
        .add_item("MNT", "Mxddab6281766ad86497741ff91b6b48fe85012e3c", "0.2")
        .build();

    auto signature = tx->sign_single(priv_key);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxMultisend, RealSend) {
    minter::privkey_t priv = minter::privkey_t::from_mnemonic("puzzle feed enlist rack cliff divert exist bind swamp kiwi casino pull");
    auto tx = minter::new_tx()
        ->set_gas_coin("BIP")
        .set_nonce("1")
        .set_gas_price("1")
        .set_chain_id(minter::testnet)
        .tx_multisend()
        ->add_item("MNT", "Mxfe60014a6e9ac91618f5d1cab3fd58cded61ee99", "0.1")
        .add_item("MNT", "Mxddab6281766ad86497741ff91b6b48fe85012e3c", "0.2")
        .build();

}

TEST(TxMultisend, TestDecode) {
    const char *encoded =
        "f8b30102018a4d4e54000000000000000db858f856f854e98a4d4e540000000000000094fe60014a6e9ac91618f5d1cab3fd58cded61ee9988016345785d8a0000e98a4d4e540000000000000094ddab6281766ad86497741ff91b6b48fe85012e3c8802c68af0bb140000808001b845f8431ca0b15dcf2e013df1a2aea02e36a17af266d8ee129cdcb3e881d15b70c9457e7571a0226af7bdaca9d42d6774c100b22e0c7ba4ec8dd664d17986318e905613013283";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_multisend>();

    ASSERT_EQ(2, data->get_items().size());
    minter::send_target t1 = data->get_items()[0];
    minter::send_target t2 = data->get_items()[1];

    ASSERT_STREQ("Mxfe60014a6e9ac91618f5d1cab3fd58cded61ee99", t1.to.to_string().c_str());
    ASSERT_STREQ("Mxddab6281766ad86497741ff91b6b48fe85012e3c", t2.to.to_string().c_str());
    ASSERT_EQ(dev::bigdec18("0.1"), t1.get_amount());
    ASSERT_EQ(dev::bigdec18("0.2"), t2.get_amount());
    ASSERT_STREQ("MNT", t1.coin.c_str());
    ASSERT_STREQ("MNT", t2.coin.c_str());
}