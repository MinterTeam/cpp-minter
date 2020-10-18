/*!
 * minter_tx.
 * tx_unbound.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_unbond.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

minter::tx_unbond::tx_unbond(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

void minter::tx_unbond::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_pub_key = (dev::bytes) rlp[0];
    m_coin_id = (dev::bigint) rlp[1];
    m_value = (dev::bigint) rlp[2];
}

uint16_t minter::tx_unbond::type() const {
    return minter::tx_unbond_type.type();
}

#include <iostream>
dev::bytes minter::tx_unbond::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_pub_key.get());
        lst.append(m_coin_id);
        lst.append(m_value);
        out.appendList(lst);
    }

    return out.out();
}

// Setters

minter::tx_unbond& minter::tx_unbond::set_pub_key(const dev::bytes& pub_key) {
    m_pub_key = pub_key;
    return *this;
}
minter::tx_unbond& minter::tx_unbond::set_pub_key(const minter::pubkey_t& pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_unbond& minter::tx_unbond::set_coin_id(const dev::bigint& coin_id) {
    m_coin_id = coin_id;
    return *this;
}

minter::tx_unbond& minter::tx_unbond::set_coin_id(const std::string& coin_id_num) {
    m_coin_id = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_unbond& minter::tx_unbond::set_value(const std::string& value) {
    m_value = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_unbond& minter::tx_unbond::set_value(const dev::bigdec18& value) {
    m_value = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_unbond& minter::tx_unbond::set_value(const dev::bigint& value) {
    m_value = value;
    return *this;
}

// Getters

const minter::pubkey_t& minter::tx_unbond::get_pub_key() const {
    return m_pub_key;
}
dev::bigint minter::tx_unbond::get_coin_id() const {
    return m_coin_id;
}
dev::bigdec18 minter::tx_unbond::get_value() const {
    return minter::utils::humanize_value(m_value);
}
