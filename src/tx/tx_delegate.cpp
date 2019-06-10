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
minter::tx_delegate::tx_delegate(std::shared_ptr<minter::tx> tx) : tx_data(std::move(tx)) {

}
uint16_t minter::tx_delegate::type() const {
    return minter::tx_delegate_type::type();
}
dev::bytes minter::tx_delegate::encode() {
    dev::RLPStream out;
    dev::RLPStream lst;
    {
        lst.append((dev::bytes)m_pub_key);
        lst.append(minter::utils::to_bytes_fixed(m_coin));
        lst.append(m_stake);

        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_delegate::decode_internal(dev::RLP rlp) {
    m_pub_key = (dev::bytes)rlp[0];
    m_coin = minter::utils::to_string_clear((dev::bytes)rlp[1]);
    m_stake = (dev::bigint)rlp[2];
}

minter::tx_delegate &minter::tx_delegate::set_pub_key(const dev::bytes &pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_delegate &minter::tx_delegate::set_pub_key(const minter::pubkey_t &pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_delegate &minter::tx_delegate::set_coin(const char *coin) {
    m_coin = std::string(coin);
    return *this;
}

minter::tx_delegate &minter::tx_delegate::set_coin(const std::string &coin) {
    m_coin = coin;
    return *this;
}

minter::tx_delegate &minter::tx_delegate::set_stake(const char *amount) {
    m_stake = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_delegate &minter::tx_delegate::set_stake(const dev::bigdec18 &amount) {
    m_stake = minter::utils::normalize_value(amount);
    return *this;
}

const minter::pubkey_t& minter::tx_delegate::get_pub_key() const {
    return m_pub_key;
}

std::string minter::tx_delegate::get_coin() const {
    return m_coin;
}

dev::bigdec18 minter::tx_delegate::get_stake() const {
    return minter::utils::humanize_value(m_stake);
}

