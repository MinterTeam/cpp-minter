/*!
 * minter_tx.
 * tx_edit_candidate.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_edit_candidate.h"
#include "minter/tx/tx_type.h"
minter::tx_edit_candidate::tx_edit_candidate(std::shared_ptr<minter::tx> tx) : tx_data(std::move(tx)) {

}

uint16_t minter::tx_edit_candidate::type() const {
    return minter::tx_edit_candidate_type::type();
}

dev::bytes minter::tx_edit_candidate::encode() {
    dev::RLPStream out;
    dev::RLPStream lst;
    {
        lst.append((dev::bytes)m_pub_key);
        lst.append(m_reward_address.get());
        lst.append(m_owner_address.get());

        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_edit_candidate::decode_internal(dev::RLP rlp) {
    m_pub_key = (dev::bytes)rlp[0];
    m_reward_address = (dev::bytes)rlp[1];
    m_owner_address = (dev::bytes)rlp[2];
}

minter::tx_edit_candidate &minter::tx_edit_candidate::set_pub_key(const minter::pubkey_t &pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_edit_candidate &minter::tx_edit_candidate::set_pub_key(const dev::bytes &pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_edit_candidate &minter::tx_edit_candidate::set_reward_address(const minter::data::address &address) {
    m_reward_address = address;
    return *this;
}

minter::tx_edit_candidate &minter::tx_edit_candidate::set_owner_address(const minter::data::address &address) {
    m_owner_address = address;
    return *this;
}

const minter::pubkey_t& minter::tx_edit_candidate::get_pub_key() const {
    return m_pub_key;
}

const minter::data::address minter::tx_edit_candidate::get_reward_address() const {
    return m_reward_address;
}

const minter::data::address minter::tx_edit_candidate::get_owner_address() const {
    return m_owner_address;
}

