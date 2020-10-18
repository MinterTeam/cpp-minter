/*!
 * minter_tx.
 * tx_sell_coin.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_sell_coin.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"
minter::tx_sell_coin::tx_sell_coin(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
uint16_t minter::tx_sell_coin::type() const {
    return minter::tx_sell_coin_type.type();
}
dev::bytes minter::tx_sell_coin::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coin_to_sell);
        lst.append(m_value_to_sell);
        lst.append(m_coin_to_buy);
        lst.append(m_min_value_to_buy);
        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_sell_coin::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_coin_to_sell = (dev::bigint) rlp[0];
    m_value_to_sell = (dev::bigint) rlp[1];
    m_coin_to_buy = (dev::bigint) rlp[2];
    m_min_value_to_buy = (dev::bigint) rlp[3];
}

minter::tx_sell_coin& minter::tx_sell_coin::set_coin_id_to_sell(const dev::bigint& coin_id) {
    m_coin_to_sell = coin_id;
    return *this;
}

minter::tx_sell_coin& minter::tx_sell_coin::set_coin_id_to_sell(const std::string& coin_id_num) {
    m_coin_to_sell = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_sell_coin& minter::tx_sell_coin::set_coin_id_to_buy(const dev::bigint& coin_id) {
    m_coin_to_buy = coin_id;
    return *this;
}

minter::tx_sell_coin& minter::tx_sell_coin::set_coin_id_to_buy(const std::string& coin_id_num) {
    m_coin_to_buy = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_sell_coin& minter::tx_sell_coin::set_value_to_sell(const std::string& amount) {
    m_value_to_sell = minter::utils::normalize_value(amount);
    return *this;
}
minter::tx_sell_coin& minter::tx_sell_coin::set_value_to_sell(const dev::bigdec18& amount) {
    m_value_to_sell = minter::utils::normalize_value(amount);
    return *this;
}
minter::tx_sell_coin& minter::tx_sell_coin::set_value_to_sell(const dev::bigint& amount) {
    m_value_to_sell = amount;
    return *this;
}

minter::tx_sell_coin& minter::tx_sell_coin::set_min_value_to_buy(const std::string& amount) {
    m_min_value_to_buy = minter::utils::normalize_value(amount);
    return *this;
}
minter::tx_sell_coin& minter::tx_sell_coin::set_min_value_to_buy(const dev::bigdec18& amount) {
    m_min_value_to_buy = minter::utils::normalize_value(amount);
    return *this;
}
minter::tx_sell_coin& minter::tx_sell_coin::set_min_value_to_buy(const dev::bigint& amount) {
    m_min_value_to_buy = amount;
    return *this;
}

dev::bigint minter::tx_sell_coin::get_coin_id_to_sell() const {
    return m_coin_to_sell;
}
dev::bigint minter::tx_sell_coin::get_coin_id_to_buy() const {
    return m_coin_to_buy;
}
dev::bigdec18 minter::tx_sell_coin::get_value_to_sell() const {
    return minter::utils::humanize_value(m_value_to_sell);
}
dev::bigdec18 minter::tx_sell_coin::get_min_value_to_buy() const {
    return minter::utils::humanize_value(m_min_value_to_buy);
}
