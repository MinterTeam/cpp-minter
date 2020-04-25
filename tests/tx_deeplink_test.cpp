/*!
 * minter_tx.
 * tx_deeplink_test.cpp
 *
 * \date 04/25/2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <iostream>
#include <minter/tx.hpp>
#include <minter/tx/tx_deeplink.h>
#include <toolbox/data/base64.h>
#include <toolbox/strings.hpp>

TEST(TxDeeplink, TestDecode) {
    //https://testnet.bip.to/tx/-QEKCbj5-Pe4sviwgzEyOAKEO5rJ_4pNTlQAAAAAAAAAiQbwW1nTsgAAAIpNTlQAAAAAAAAAuEG1nJoR7nml2-bkA4Ol21qQlgtFLl_dxjzI89CS6_fjkwM0DY9CvaO1Wmgbns4yKfnPcY1xfvDCy4GMUqm5PyfZABygr-X0xZ8aH2S9LXu5fw_Ay7nPG0DRLcWflI3EGbutUfigUDO5jnQ6nSrzKeiQkz6lhXhVc9OkD1Kqp2hYCD1oZU64QRM4JAJ73fdRIMk88YP1_xi-6pw1AgPrevAry7vKXigiAe_n5OrCSU3oW3Yilt1LfqeHmyOKbdiwEoOO5vwE1RUBgIABik1OVAAAAAAAAAA
    const std::string deeplinkRaw = "-QEKCbj5-Pe4sviwgzEyOAKEO5rJ_4pNTlQAAAAAAAAAiQbwW1nTsgAAAIpNTlQAAAAAAAAAuEG1nJoR7nml2-bkA4Ol21qQlgtFLl_dxjzI89CS6_fjkwM0DY9CvaO1Wmgbns4yKfnPcY1xfvDCy4GMUqm5PyfZABygr-X0xZ8aH2S9LXu5fw_Ay7nPG0DRLcWflI3EGbutUfigUDO5jnQ6nSrzKeiQkz6lhXhVc9OkD1Kqp2hYCD1oZU64QRM4JAJ73fdRIMk88YP1_xi-6pw1AgPrevAry7vKXigiAe_n5OrCSU3oW3Yilt1LfqeHmyOKbdiwEoOO5vwE1RUBgIABik1OVAAAAAAAAAA";

    dev::bytes_data deepLinkData = dev::bytes_data::from_string_raw(deeplinkRaw);
    deepLinkData.switch_map(minter::utils::from_base64_web);

    std::shared_ptr<minter::tx_deeplink> deeplink = minter::tx_deeplink::decode(deepLinkData);
    std::shared_ptr<minter::tx> tx = deeplink->get_tx();

    std::cout << "nonce:     " << minter::utils::to_string(tx->get_nonce()) << std::endl;
    std::cout << "gas coin:  " << tx->get_gas_coin() << std::endl;
    std::cout << "gas price: " << minter::utils::to_string(tx->get_gas_price()) << std::endl;
    std::cout << "payload:   \"" << dev::bytes_data(tx->get_payload()).to_string() << "\"" << std::endl;
    std::cout << "type:      " << ((int) tx->get_type()) << std::endl;

    switch (tx->get_type()) {
    case minter::tx_redeem_check_type.type(): {
        std::cout << "Redeem check data:" << std::endl;
        std::shared_ptr<minter::tx_redeem_check> data = tx->get_data<minter::tx_redeem_check>();
        std::cout << "  check: " << dev::bytes_data(data->get_check()).to_hex() << std::endl;
        std::cout << "  proof: " << dev::bytes_data(data->get_proof()).to_hex() << std::endl;
    }
    }
}

TEST(TxDeepLink, TestEncode) {
    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce(dev::bigint("0"));
    tx_builder->set_gas_price(dev::bigint("1"));
    tx_builder->set_gas_coin("MNT");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mx8d008dffe2f9144a39a2094ebdedadad335e814f");
    data->set_value("1");
    data->set_coin("MNT");
    auto tx = data->build();

    ASSERT_STREQ(
        "a39f86aae7eba8300a527d05be1d2d48e293310efeeb994ff06fc4701230ee03",
        tx->get_unsigned_hash().to_hex().c_str());

    auto tx_deeplink = minter::tx_deeplink(std::move(tx));
    dev::bytes_data deeplinkRaw = tx_deeplink.encode();
    deeplinkRaw.switch_map(minter::utils::to_base64_web);

    // output is base64 for web
    std::cout << deeplinkRaw.to_string() << std::endl;

    ASSERT_STREQ("-DoBqumKTU5UAAAAAAAAAJSNAI3_4vkUSjmiCU697a2tM16BT4gN4Lazp2QAAICAAYpNTlQAAAAAAAAA", deeplinkRaw.to_string().c_str());

    ASSERT_STREQ(
        "https://testnet.bip.to/tx/-DoBqumKTU5UAAAAAAAAAJSNAI3_4vkUSjmiCU697a2tM16BT4gN4Lazp2QAAICAAYpNTlQAAAAAAAAA",
        tx_deeplink.to_url("https://testnet.bip.to").c_str());

    ASSERT_STREQ(
        "https://testnet.bip.to/tx/-DoBqumKTU5UAAAAAAAAAJSNAI3_4vkUSjmiCU697a2tM16BT4gN4Lazp2QAAICAAYpNTlQAAAAAAAAA",
        tx_deeplink.to_url("https://testnet.bip.to/").c_str());

    ASSERT_STREQ(
        "https://bip.to/tx/-DoBqumKTU5UAAAAAAAAAJSNAI3_4vkUSjmiCU697a2tM16BT4gN4Lazp2QAAICAAYpNTlQAAAAAAAAA",
        tx_deeplink.to_url().c_str());
}