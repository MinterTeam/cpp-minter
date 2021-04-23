/*!
 * minter_tx.
 * tx_buy_coin.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_buy_coin.h"

#include <utility>

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

minter::tx_buy_coin::tx_buy_coin(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
uint16_t minter::tx_buy_coin::type() const {
    return minter::tx_buy_coin_type.type();
}
dev::bytes minter::tx_buy_coin::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coin_id_to_buy);
        lst.append(m_value_to_buy);
        lst.append(m_coin_id_to_sell);
        lst.append(m_max_value_to_sell);
        out.appendList(lst);
    }
    return out.out();
}
void minter::tx_buy_coin::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_coin_id_to_buy = minter::utils::to_bigint((dev::bytes) rlp[0]);
    m_value_to_buy = minter::utils::to_bigint((dev::bytes) rlp[1]);
    m_coin_id_to_sell = minter::utils::to_bigint((dev::bytes) rlp[2]);
    m_max_value_to_sell = minter::utils::to_bigint((dev::bytes) rlp[3]);
}

dev::bigint minter::tx_buy_coin::get_coin_id_to_buy() const {
    return m_coin_id_to_buy;
}

dev::bigint minter::tx_buy_coin::get_coin_id_to_sell() const {
    return m_coin_id_to_sell;
}

dev::bigdec18 minter::tx_buy_coin::get_value_to_buy() const {
    return minter::utils::humanize_value(m_value_to_buy);
}

dev::bigdec18 minter::tx_buy_coin::get_max_value_to_sell() const {
    return minter::utils::humanize_value(m_max_value_to_sell);
}

minter::tx_buy_coin& minter::tx_buy_coin::set_coin_id_to_buy(dev::bigint coin_id) {
    m_coin_id_to_buy = std::move(coin_id);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_coin_id_to_buy(const std::string& coin_id_num) {
    m_coin_id_to_buy = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_value_to_buy(const std::string& value) {
    m_value_to_buy = minter::utils::normalize_value(value);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_value_to_buy(const dev::bigdec18& value) {
    m_value_to_buy = minter::utils::normalize_value(value);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_value_to_buy(dev::bigint value) {
    m_value_to_buy = std::move(value);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_coin_id_to_sell(dev::bigint coin_id) {
    m_coin_id_to_sell = std::move(coin_id);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_coin_id_to_sell(const std::string& coin_id_num) {
    m_coin_id_to_sell = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_max_value_to_sell(const std::string& value) {
    m_max_value_to_sell = minter::utils::normalize_value(value);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_max_value_to_sell(const dev::bigdec18& valueDec) {
    m_max_value_to_sell = minter::utils::normalize_value(valueDec);
    return *this;
}

minter::tx_buy_coin& minter::tx_buy_coin::set_max_value_to_sell(dev::bigint value) {
    m_max_value_to_sell = std::move(value);
    return *this;
}
