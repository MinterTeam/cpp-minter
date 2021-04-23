/*!
 * minter_tx.
 * tx_delegate.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_delegate.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

#include <utility>
minter::tx_delegate::tx_delegate(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
uint16_t minter::tx_delegate::type() const {
    return minter::tx_delegate_type.type();
}
dev::bytes minter::tx_delegate::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_pub_key.get());
        lst.append(m_coin_id);
        lst.append(m_stake);

        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_delegate::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_pub_key = (dev::bytes) rlp[0];
    m_coin_id = (dev::bigint) rlp[1];
    m_stake = (dev::bigint) rlp[2];
}

minter::tx_delegate& minter::tx_delegate::set_pub_key(const minter::pubkey_t& pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_delegate& minter::tx_delegate::set_coin_id(dev::bigint coin_id) {
    m_coin_id = std::move(coin_id);
    return *this;
}

minter::tx_delegate& minter::tx_delegate::set_coin_id(const std::string& coin_id_num) {
    m_coin_id = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_delegate& minter::tx_delegate::set_stake(const std::string& amount) {
    m_stake = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_delegate& minter::tx_delegate::set_stake(dev::bigint amount) {
    m_stake = std::move(amount);
    return *this;
}

minter::tx_delegate& minter::tx_delegate::set_stake(const dev::bigdec18& amount) {
    m_stake = minter::utils::normalize_value(amount);
    return *this;
}

const minter::pubkey_t& minter::tx_delegate::get_pub_key() const {
    return m_pub_key;
}

dev::bigint minter::tx_delegate::get_coin_id() const {
    return m_coin_id;
}

dev::bigdec18 minter::tx_delegate::get_stake() const {
    return minter::utils::humanize_value(m_stake);
}
