/*!
 * minter_tx.
 * tx_create_multisig_address.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_create_multisig_address.h"

#include "minter/tx/tx_type.h"

#include <algorithm>

minter::tx_create_multisig_address::tx_create_multisig_address(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
uint16_t minter::tx_create_multisig_address::type() const {
    return minter::tx_create_multisig_address_type.type();
}
dev::bytes minter::tx_create_multisig_address::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_threshold);
        lst.append(m_weights);
        lst.append(m_addresses);

        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_create_multisig_address::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_threshold = (dev::bigint) rlp[0];
    m_weights = rlp[1].toVector<dev::bigint>();

    std::vector<dev::bytes> addresses = rlp[2].toVector<dev::bytes>();
    std::for_each(addresses.begin(), addresses.end(), [this](const dev::bytes& add) {
        m_addresses.push_back(minter::data::address(std::move(add)));
    });
}

unsigned minter::tx_create_multisig_address::get_threshold() const {
    return static_cast<unsigned>(m_threshold);
}

const std::vector<minter::data::address>& minter::tx_create_multisig_address::get_addresses() const {
    return m_addresses;
}

const std::vector<dev::bigint>& minter::tx_create_multisig_address::get_weights() const {
    return m_weights;
}

minter::tx_create_multisig_address& minter::tx_create_multisig_address::set_threshold(unsigned threshold) {
    m_threshold = dev::bigint(threshold);
    return *this;
}

minter::tx_create_multisig_address& minter::tx_create_multisig_address::add_address(const minter::address_t& address, unsigned weight) {
    m_addresses.push_back(address);
    m_weights.push_back(dev::bigint(weight));
    return *this;
}
