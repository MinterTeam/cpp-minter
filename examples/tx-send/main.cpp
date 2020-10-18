/*!
 * minter.
 * make_send_tx.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <minter/address.h>
#include <minter/private_key.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_send_coin.h>

int main() {
    // create transactions build: here we're setting common transaction data
    // auto = std::shared_ptr<minter::tx_builder>
    auto tx_builder = minter::new_tx();
    // set nonce
    tx_builder->set_nonce("1");

    // set gas price
    tx_builder->set_gas_price("1");

    // set gas coin
    tx_builder->set_gas_coin_id("0");

    // Set network id: minter::testnet or minter::mainnet
    tx_builder->set_chain_id(minter::testnet);

    // create specific transaction: in this case is a "send" transaction
    // auto = std::shared_ptr<minter::tx_send_coin>
    auto data = tx_builder->tx_send_coin();

    // set "send" recipient
    data->set_to("Mx0000000000000000000000000000000000000000");
    // set amount to send
    data->set_value("10");
    // set coin to send
    data->set_coin_id("0");

    // finalize transaction
    auto tx = data->build();

    // create private key instance to sign transaction with
    minter::privkey_t pk("df1f236d0396cc43147e44206c341a65573326e907d033690e31a21323c03a9f");

    // sign transaction: result is a dev::bytes_data - useful bytes wrapper
    auto signedTx = tx->sign_single(pk);

    // now u can use signed as you wish

    // print
    std::cout << signedTx.to_hex() << std::endl;

    // or do smthng
    const uint8_t* signed_tx_data = signedTx.cdata();

    return 0;
}
