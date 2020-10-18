/*!
 * minter_tx.
 * tx_edit_multisig.cpp
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_edit_multisig.h"

#include "minter/tx/tx_type.h"

minter::tx_edit_multisig::tx_edit_multisig(std::shared_ptr<minter::tx> tx)
    : tx_data(tx),
      tx_create_multisig_address(tx) {
}

uint16_t minter::tx_edit_multisig::type() const {
    return tx_edit_multisig_type.type();
}
dev::bytes minter::tx_edit_multisig::encode() {
    return tx_create_multisig_address::encode();
}
void minter::tx_edit_multisig::decode(const dev::bytes& data) {
    tx_create_multisig_address::decode(data);
}
minter::tx_edit_multisig& minter::tx_edit_multisig::set_threshold(unsigned int threshold) {
    tx_create_multisig_address::set_threshold(threshold);
    return *this;
}
minter::tx_edit_multisig& minter::tx_edit_multisig::add_address(const minter::address_t& address, unsigned int weight) {
    tx_create_multisig_address::add_address(address, weight);
    return *this;
}
