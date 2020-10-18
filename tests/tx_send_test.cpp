/*!
 * minter_tx.
 * tx_send_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/crypto/cxx_secp256k1.h"
#include "minter/private_key.h"
#include "minter/tx/tx.h"
#include "minter/tx/tx_builder.h"
#include "minter/tx/tx_send_coin.h"

#include <gtest/gtest.h>
#include <toolbox/strings.hpp>

/* todo: fix and test this thing
static minter::signature test_signer_func(dev::bytes_32 hash) {
    minter::privkey_t pk("33671c8f2363dffb45e166f1cadced9aa5f86ad32509e5c4f0b39257c30b4110");
    minter::cxx_secp256k1 ctx;
    secp256k1_ecdsa_recoverable_signature sig;

    int ret = secp256k1_ecdsa_sign_recoverable(ctx.get(), &sig, hash.cdata(), pk.cdata(), NULL, NULL);

    uint8_t outputSer[65];
    minter::signature outSig;
    int recoveryId = 0;

    if (ret) {
        int serializeRet = secp256k1_ecdsa_recoverable_signature_serialize_compact(
            ctx.get(),
            outputSer,
            &recoveryId,
            &sig);
        (void) serializeRet;
        outputSer[64] = ((uint8_t) recoveryId) + (uint8_t) 27;
    } else {
        return outSig;
    }

    uint8_t r[32], s[32], v[1];
    memcpy(r, outputSer + 0, 32);
    memcpy(s, outputSer + 32, 32);
    v[0] = outputSer[64];
    memset(outputSer, 0, 65);

    outSig.r = dev::bytes(r, r + 32);
    outSig.s = dev::bytes(s, s + 32);
    outSig.v = dev::bytes(v, v + 1);
    outSig.success = true;

    return outSig;
}
 */

TEST(TxSend, TestSendEncode) {
    const char* expectedTx = "f86f01010180019fde809467691076548b20234461ff6fd2bc9c64393eb8fc872bdbb64bc09000808001b845f8431ca08be3f0c3aecc80ec97332e8aa39f20cd9e735092c0de37eb726d8d3d0a255a66a02040a1001d1a9116317eb24aa7ee4730ed980bd08a1fc0adb4e7598425178d3a";
    minter::privkey_t pk("4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e");
    minter::address_t address = "Mx67691076548b20234461ff6fd2bc9c64393eb8fc";

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_chain_id(minter::mainnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to(address);
    data->set_value("0.012345");
    data->set_coin_id("0");
    auto tx = data->build();

    auto signedTx = tx->sign_single(pk);

    {
        auto decoded = minter::tx::decode(signedTx.to_hex().c_str());
        ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
        ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
        ASSERT_EQ(minter::mainnet, decoded->get_chain_id());
        ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
        ASSERT_EQ((uint8_t) 0x01, decoded->get_type());
        ASSERT_EQ(dev::bytes(0), decoded->get_service_data());
        ASSERT_EQ(dev::bytes(0), decoded->get_payload());
        ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
        std::shared_ptr<minter::tx_send_coin> data = decoded->get_data<minter::tx_send_coin>();
        ASSERT_EQ(address, data->get_to());
        ASSERT_EQ(dev::bigdec18("0.012345"), data->get_value());
        ASSERT_EQ(dev::bigint("0"), data->get_coin_id());
    }

    ASSERT_STREQ(expectedTx, signedTx.to_hex().c_str());
}

TEST(TxSend, TestSendDecode) {
    const char* encoded = "f86f01010180019fde809467691076548b20234461ff6fd2bc9c64393eb8fc872bdbb64bc09000808001b845f8431ca08be3f0c3aecc80ec97332e8aa39f20cd9e735092c0de37eb726d8d3d0a255a66a02040a1001d1a9116317eb24aa7ee4730ed980bd08a1fc0adb4e7598425178d3a";

    std::shared_ptr<minter::tx> decoded = minter::tx::decode(encoded);
    minter::address_t exAddress = "Mx67691076548b20234461ff6fd2bc9c64393eb8fc";

    ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_NE(dev::bigint("2"), decoded->get_gas_price());
    ASSERT_EQ(minter::mainnet, decoded->get_chain_id());
    std::shared_ptr<minter::tx_send_coin> data = decoded->get_data<minter::tx_send_coin>();
    ASSERT_EQ(exAddress, data->get_to());
    ASSERT_EQ(dev::bigdec18("0.012345"), data->get_value());
    ASSERT_EQ(dev::bigint("0"), data->get_coin_id());
}
