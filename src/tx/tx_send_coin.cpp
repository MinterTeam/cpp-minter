/*!
 * minter_tx.
 * tx_send_coin.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <minter/bip39/utils.h>
#include <minter/tx/utils.h>
#include <minter/tx/tx_send_coin.h>
#include <minter/tx/tx_type.h>

minter::tx_send_coin::tx_send_coin(std::shared_ptr<minter::tx> tx) : tx_data(std::move(tx)) {
}

minter::tx_send_coin &minter::tx_send_coin::set_coin(const std::string &coin) {
    m_coin = coin;
    return *this;
}
minter::tx_send_coin &minter::tx_send_coin::set_coin(std::string &&coin) {
    m_coin = std::move(coin);
    return *this;
}
minter::tx_send_coin &minter::tx_send_coin::set_coin(const char *coin) {
    m_coin = std::string(coin);
    return *this;
}

minter::tx_send_coin &minter::tx_send_coin::set_to(const char *address) {
    return set_to(minter::data::address(address));
}

minter::tx_send_coin &minter::tx_send_coin::set_to(const std::string &address) {
    return set_to(address.c_str());
}

minter::tx_send_coin &minter::tx_send_coin::set_to(const minter::data::address &address) {
    m_to = address;
    return *this;
}

minter::tx_send_coin &minter::tx_send_coin::set_value(const std::string &normalized) {
    m_value = minter::utils::normalize_value(normalized);
    return *this;
}

minter::tx_send_coin &minter::tx_send_coin::set_value(const dev::bigdec18 &normalized) {
    m_value = minter::utils::normalize_value(normalized);
    return *this;
}

minter::tx_send_coin &minter::tx_send_coin::set_value(const dev::bigint &raw) {
    m_value = raw;
    return *this;
}

uint16_t minter::tx_send_coin::type() const {
    return minter::tx_send_coin_type::type();
}

std::string minter::tx_send_coin::get_coin() const {
    return minter::utils::strip_null_bytes(m_coin.c_str(), m_coin.size());
}

const minter::data::address& minter::tx_send_coin::get_to() const {
    return m_to;
}

dev::bigdec18 minter::tx_send_coin::get_value() const {
    return minter::utils::humanize_value(m_value);
}

dev::bytes minter::tx_send_coin::encode() {
    dev::RLPStream out;
    dev::RLPStream lst;
    {
        lst.append(minter::utils::to_bytes_fixed(m_coin));
        lst.append(m_to.get());
        lst.append(m_value);
        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_send_coin::decode_internal(dev::RLP rlp) {
    m_coin = (std::string)rlp[0];
    m_to = minter::data::address((dev::bytes)rlp[1]);
    m_value = (dev::bigint)rlp[2];
}

