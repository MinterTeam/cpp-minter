/*!
 * minter_tx.
 * tx_create_multisig_address.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_CREATE_MULTISIG_ADDRESS_H
#define MINTER_TX_CREATE_MULTISIG_ADDRESS_H

#include "minter/address.h"
#include "tx_data.h"

#include <vector>

namespace minter {

class MINTER_TX_API tx_create_multisig_address : public virtual minter::tx_data {
public:
    explicit tx_create_multisig_address(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    unsigned get_threshold() const;
    const std::vector<dev::bigint>& get_weights() const;
    const std::vector<minter::address_t>& get_addresses() const;

    tx_create_multisig_address& set_threshold(unsigned threshold);
    tx_create_multisig_address& add_address(const minter::address_t& address, unsigned weight);

protected:
    dev::bigint m_threshold;
    std::vector<dev::bigint> m_weights;
    std::vector<minter::address_t> m_addresses;
};

} // namespace minter

#endif //MINTER_TX_CREATE_MULTISIG_ADDRESS_H
