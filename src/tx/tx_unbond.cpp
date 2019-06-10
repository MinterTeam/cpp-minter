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
        :tx_data(std::move(tx)) {

}

void minter::tx_unbond::decode_internal(dev::RLP rlp) {
    m_pub_key = (dev::bytes)rlp[0];
    m_coin = minter::utils::to_string_clear((dev::bytes)rlp[1]);
    m_value = (dev::bigint) rlp[2];
}

uint16_t minter::tx_unbond::type() const {
    return minter::tx_unbond_type::type();
}

#include <iostream>
dev::bytes minter::tx_unbond::encode() {
    dev::RLPStream out;
    dev::RLPStream lst;
    {
        lst.append((dev::bytes)m_pub_key);
        lst.append(minter::utils::to_bytes_fixed(m_coin, 10));
        lst.append(m_value);
        out.appendList(lst);
    }

    return out.out();
}

minter::tx_unbond &minter::tx_unbond::set_pub_key(const dev::bytes &pub_key) {
    m_pub_key = pub_key;
    return *this;
}
minter::tx_unbond &minter::tx_unbond::set_pub_key(const minter::pubkey_t &pub_key) {
    m_pub_key = pub_key;
    return *this;
}
minter::tx_unbond &minter::tx_unbond::set_coin(const char* coin) {
    m_coin = std::string(coin);
    return *this;
}
minter::tx_unbond &minter::tx_unbond::set_coin(const std::string &coin) {
    m_coin = coin;
    return *this;
}
minter::tx_unbond &minter::tx_unbond::set_value(const char* value) {
    m_value = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_unbond &minter::tx_unbond::set_value(const dev::bigdec18 &value) {
    m_value = minter::utils::normalize_value(value);
    return *this;
}
const minter::pubkey_t &minter::tx_unbond::get_pub_key() const {
    return m_pub_key;
}
std::string minter::tx_unbond::get_coin() const {
    return m_coin;
}
dev::bigdec18 minter::tx_unbond::get_value() const {
    return minter::utils::humanize_value(m_value);
}
