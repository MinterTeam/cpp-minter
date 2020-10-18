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
#include <minter/tx/tx_edit_coin_owner.h>

TEST(TxEditCoinOwner, TestEncode) {
    const char* expected = "f8710b01018011a1e08a5355504552544553543194d82558ea00eb81d35f2654953598f5d51737d31c808001b845f8431ca07ec736f2bebcafb9628603c3837dd75a18e76f29bdeae6ecdce635ca8519ae00a04715b58493660840957d5cce0311a2f2caf7a3c14f7f3afaad3ec6c47f91d932";
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id(dev::bigint("0"))
                  .set_nonce(dev::bigint("11"))
                  .set_gas_price("1")
                  .set_chain_id(minter::mainnet)
                  .tx_edit_coin_owner()
                  ->set_new_owner(minter::address_t("Mxd82558ea00eb81d35f2654953598f5d51737d31c"))
                  .set_symbol("SUPERTEST1")
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxEditCoinOwner, TestDecode) {
    const char* encoded = "f8710b01018011a1e08a5355504552544553543194d82558ea00eb81d35f2654953598f5d51737d31c808001b845f8431ca07ec736f2bebcafb9628603c3837dd75a18e76f29bdeae6ecdce635ca8519ae00a04715b58493660840957d5cce0311a2f2caf7a3c14f7f3afaad3ec6c47f91d932";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_edit_coin_owner>();

    ASSERT_EQ(minter::address_t("Mxd82558ea00eb81d35f2654953598f5d51737d31c"), data->get_new_owner());
    ASSERT_STREQ("SUPERTEST1", data->get_symbol().c_str());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
}