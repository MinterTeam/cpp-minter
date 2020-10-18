/*!
 * minter_tx.
 * tx_send_coin.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <minter/tx/tx_send_coin.h>
#include <minter/tx/tx_type.h>
#include <minter/tx/utils.h>

minter::tx_send_coin::tx_send_coin(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

minter::tx_send_coin& minter::tx_send_coin::set_coin_id(const dev::bigint& coin_id) {
    m_coin_id = coin_id;
    return *this;
}

minter::tx_send_coin& minter::tx_send_coin::set_coin_id(const std::string& coin_id_num) {
    m_coin_id = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_send_coin& minter::tx_send_coin::set_to(const minter::address_t& address) {
    m_to = address;
    return *this;
}

minter::tx_send_coin& minter::tx_send_coin::set_value(const std::string& value) {
    m_value = minter::utils::normalize_value(value);
    return *this;
}

minter::tx_send_coin& minter::tx_send_coin::set_value(const dev::bigdec18& value) {
    m_value = minter::utils::normalize_value(value);
    return *this;
}

minter::tx_send_coin& minter::tx_send_coin::set_value(const dev::bigint& value) {
    m_value = value;
    return *this;
}

uint16_t minter::tx_send_coin::type() const {
    return minter::tx_send_coin_type.type();
}

dev::bigint minter::tx_send_coin::get_coin_id() const {
    return m_coin_id;
}

const minter::data::address& minter::tx_send_coin::get_to() const {
    return m_to;
}

dev::bigdec18 minter::tx_send_coin::get_value() const {
    return minter::utils::humanize_value(m_value);
}

dev::bytes minter::tx_send_coin::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coin_id);
        lst.append(m_to.get());
        lst.append(m_value);
        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_send_coin::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_coin_id = (dev::bigint) rlp[0];
    m_to = minter::data::address((dev::bytes) rlp[1]);
    m_value = (dev::bigint) rlp[2];
}
