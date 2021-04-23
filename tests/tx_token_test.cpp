/*!
 * minter_tx.
 * tx_token_test.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include <gtest/gtest.h>
#include <minter/public_key.h>
#include <minter/tx.hpp>
#include <minter/tx/signature_data.h>
#include <minter/tx/tx.h>
#include <minter/tx/tx_create_token.h>
#include <minter/tx/tx_recreate_token.h>
#include <minter/tx/tx_mint_token.h>
#include <minter/tx/tx_burn_token.h>

TEST(TxCreateToken, Encode) {
    const char* expected = "f883130201801eb3f28e4255524e41424c4520544f4b454e8a4255524e41424c4500008a34f086f3b33b684000008a3f870857a3e0e38000008001808001b845f8431ba03803675da057cde3bf43a085d1c774a93f3f038e843626d42d26bcdc92310e1fa002c77de52d499f65d03d159672c88e1cd9262048c60904b5a80a5065aa37fce1";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("19");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_create_token();
    data->set_name("BURNABLE TOKEN");
    data->set_ticker("BURNABLE");
    data->set_initial_amount("250000");
    data->set_max_supply("300000");
    data->set_mintable(false);
    data->set_burnable(true);

    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxCreateToken, Decode) {
    const char* encoded = "f883130201801eb3f28e4255524e41424c4520544f4b454e8a4255524e41424c4500008a34f086f3b33b684000008a3f870857a3e0e38000008001808001b845f8431ba03803675da057cde3bf43a085d1c774a93f3f038e843626d42d26bcdc92310e1fa002c77de52d499f65d03d159672c88e1cd9262048c60904b5a80a5065aa37fce1";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_create_token>();

    ASSERT_EQ(minter::tx_create_token_type.type(), decoded->get_type());

    ASSERT_STREQ("BURNABLE TOKEN", data->get_name().c_str());
    ASSERT_STREQ("BURNABLE", data->get_ticker().c_str());
    ASSERT_EQ(dev::bigdec18("250000"), data->get_initial_amount());
    ASSERT_EQ(dev::bigdec18("300000"), data->get_max_supply());
    ASSERT_FALSE(data->is_mintable());
    ASSERT_TRUE(data->is_burnable());
}

TEST(TxReCreateToken, Encode) {
    const char* expected = "f8901e0201801fb83ff83d994255524e41424c452026204d494e5441424c4520544f4b454e8a4255524e41424c4500008ad3c20dee1639f99c00008ad3c20dee1639f99c00000101808001b845f8431ca082c41369313d7d2c2fc1c455a2d1a0458da8f647ddbf45601f2edbef2299c5ffa06788aaeec5abff26d91f1d482903cb41fa57c34823e014aa711099f31b94a3be";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("30");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_recreate_token();
    data->set_name("BURNABLE & MINTABLE TOKEN");
    data->set_ticker("BURNABLE");
    data->set_initial_amount("999999");
    data->set_max_supply("999999");
    data->set_mintable(true);
    data->set_burnable(true);

    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxReCreateToken, Decode) {
    const char* encoded = "f8901e0201801fb83ff83d994255524e41424c452026204d494e5441424c4520544f4b454e8a4255524e41424c4500008ad3c20dee1639f99c00008ad3c20dee1639f99c00000101808001b845f8431ca082c41369313d7d2c2fc1c455a2d1a0458da8f647ddbf45601f2edbef2299c5ffa06788aaeec5abff26d91f1d482903cb41fa57c34823e014aa711099f31b94a3be";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_recreate_token>();

    ASSERT_EQ(minter::tx_recreate_token_type.type(), decoded->get_type());

    ASSERT_STREQ("BURNABLE & MINTABLE TOKEN", data->get_name().c_str());
    ASSERT_STREQ("BURNABLE", data->get_ticker().c_str());
    ASSERT_EQ(dev::bigdec18("999999"), data->get_initial_amount());
    ASSERT_EQ(dev::bigdec18("999999"), data->get_max_supply());
    ASSERT_TRUE(data->is_mintable());
    ASSERT_TRUE(data->is_burnable());
}

TEST(TxMintToken, Encode) {
    const char* expected = "f85c170201801c8ccb0389878678326eac900000808001b845f8431ba0dd78fa0dfb782d99d3f0983917ff8b73e571cbd56eb694bfd570368a31453abca07a6d86ed82e5de41ad27588a7e71b7030abb258c6992d38f4b995c1184ebf745";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("23");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_mint_token();
    data->set_coin_id("3");
    data->set_value("2500");

    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxMintToken, Decode) {
    const char* encoded = "f85c170201801c8ccb0389878678326eac900000808001b845f8431ba0dd78fa0dfb782d99d3f0983917ff8b73e571cbd56eb694bfd570368a31453abca07a6d86ed82e5de41ad27588a7e71b7030abb258c6992d38f4b995c1184ebf745";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_mint_token>();

    ASSERT_EQ(minter::tx_mint_token_type.type(), decoded->get_type());

    ASSERT_EQ(dev::bigint("3"), data->get_coin_id());
    ASSERT_EQ(dev::bigdec18("2500"), data->get_value());
}

TEST(TxBurnToken, Encode) {
    const char* expected = "f85c180201801d8ccb0489878678326eac900000808001b845f8431ba0903a9bd68dfe002346698b111b2010e02a5fedc9094e0d4588659d28f38dca0ba03118723f4f6b32a068ab4981c666dd264ee7216c90e73d8d34129ed37b9b69b8";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("24");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_burn_token();
    data->set_coin_id("4");
    data->set_value("2500");

    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxBurnToken, Decode) {
    const char* encoded = "f85c180201801d8ccb0489878678326eac900000808001b845f8431ba0903a9bd68dfe002346698b111b2010e02a5fedc9094e0d4588659d28f38dca0ba03118723f4f6b32a068ab4981c666dd264ee7216c90e73d8d34129ed37b9b69b8";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_burn_token>();

    ASSERT_EQ(minter::tx_burn_token_type.type(), decoded->get_type());

    ASSERT_EQ(dev::bigint("4"), data->get_coin_id());
    ASSERT_EQ(dev::bigdec18("2500"), data->get_value());
}
