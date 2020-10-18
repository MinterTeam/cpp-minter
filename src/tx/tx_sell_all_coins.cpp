/*!
 * minter_tx.
 * tx_sell_all_coins.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_sell_all_coins.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"
minter::tx_sell_all_coins::tx_sell_all_coins(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_sell_all_coins::type() const {
    return minter::tx_sell_all_coins_type.type();
}
dev::bytes minter::tx_sell_all_coins::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coin_id_to_sell);
        lst.append(m_coin_id_to_buy);
        lst.append(m_min_value_to_buy);
        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_sell_all_coins::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_coin_id_to_sell = (dev::bigint) rlp[0];
    m_coin_id_to_buy = (dev::bigint) rlp[1];
    m_min_value_to_buy = (dev::bigint) rlp[2];
}

minter::tx_sell_all_coins& minter::tx_sell_all_coins::set_coin_id_to_sell(const dev::bigint& coin_id) {
    m_coin_id_to_sell = coin_id;
    return *this;
}

minter::tx_sell_all_coins& minter::tx_sell_all_coins::set_coin_id_to_sell(const std::string& coin_id_num) {
    m_coin_id_to_sell = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_sell_all_coins& minter::tx_sell_all_coins::set_coin_id_to_buy(const dev::bigint& coin_id) {
    m_coin_id_to_buy = coin_id;
    return *this;
}

minter::tx_sell_all_coins& minter::tx_sell_all_coins::set_coin_id_to_buy(const std::string& coin_id_num) {
    m_coin_id_to_buy = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_sell_all_coins& minter::tx_sell_all_coins::set_min_value_to_buy(const std::string& amount) {
    m_min_value_to_buy = minter::utils::normalize_value(amount);
    return *this;
}
minter::tx_sell_all_coins& minter::tx_sell_all_coins::set_min_value_to_buy(const dev::bigdec18& amount) {
    m_min_value_to_buy = minter::utils::normalize_value(amount);
    return *this;
}
minter::tx_sell_all_coins& minter::tx_sell_all_coins::set_min_value_to_buy(const dev::bigint& amount) {
    m_min_value_to_buy = amount;
    return *this;
}
dev::bigint minter::tx_sell_all_coins::get_coin_id_to_sell() const {
    return m_coin_id_to_sell;
}
dev::bigint minter::tx_sell_all_coins::get_coin_id_to_buy() const {
    return m_coin_id_to_buy;
}
dev::bigdec18 minter::tx_sell_all_coins::get_min_value_to_buy() const {
    return minter::utils::humanize_value(m_min_value_to_buy);
}
