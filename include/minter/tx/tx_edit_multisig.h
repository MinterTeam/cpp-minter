/*!
 * minter_tx.
 * tx_edit_multisig.h
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_EDIT_MULTISIG_H
#define MINTER_TX_TX_EDIT_MULTISIG_H

#include "tx_create_multisig_address.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_edit_multisig : public minter::tx_create_multisig_address {
public:
    explicit tx_edit_multisig(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_edit_multisig& set_threshold(unsigned threshold);
    tx_edit_multisig& add_address(const minter::address_t& address, unsigned weight);
};

} //namespace minter

#endif //MINTER_TX_TX_EDIT_MULTISIG_H
