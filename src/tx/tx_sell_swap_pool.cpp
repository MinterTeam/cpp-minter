/*!
 * minter_tx.
 * tx_sell_swap_pool.cpp.c
 *
 * \date 03/23/2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_sell_swap_pool.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

#include <utility>

minter::tx_sell_swap_pool::tx_sell_swap_pool(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_sell_swap_pool::type() const {
    return minter::tx_sell_swap_pool_type.type();
}
dev::bytes minter::tx_sell_swap_pool::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coins);
        lst.append(m_value_to_sell);
        lst.append(m_min_value_to_buy);
        out.appendList(lst);
    }
    return out.out();
}
void minter::tx_sell_swap_pool::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    std::vector<dev::bytes> coins_raw = (std::vector<dev::bytes>) rlp[0];
    std::for_each(coins_raw.begin(), coins_raw.end(), [this](const dev::bytes& coin) {
        m_coins.push_back(minter::utils::to_bigint(coin));
    });
    m_value_to_sell = minter::utils::to_bigint((dev::bytes) rlp[1]);
    m_min_value_to_buy = minter::utils::to_bigint((dev::bytes) rlp[2]);
}

std::vector<dev::bigint> minter::tx_sell_swap_pool::get_coins() const {
    return m_coins;
}
dev::bigdec18 minter::tx_sell_swap_pool::get_value_to_sell() const {
    return minter::utils::humanize_value(m_value_to_sell);
}
dev::bigdec18 minter::tx_sell_swap_pool::get_min_value_to_buy() const {
    return minter::utils::humanize_value(m_min_value_to_buy);
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::add_coin(dev::bigint coin) {
    m_coins.push_back(std::move(coin));
    return *this;
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::add_coin(const std::string& coin_id_num) {
    m_coins.emplace_back(coin_id_num);
    return *this;
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::clear_coins() {
    m_coins.clear();
    return *this;
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::set_value_to_sell(const std::string& value) {
    m_value_to_sell = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::set_value_to_sell(const dev::bigdec18& value) {
    m_value_to_sell = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::set_value_to_sell(dev::bigint value) {
    m_value_to_sell = std::move(value);
    return *this;
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::set_min_value_to_buy(const std::string& value) {
    m_min_value_to_buy = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::set_min_value_to_buy(const dev::bigdec18& value) {
    m_min_value_to_buy = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_sell_swap_pool& minter::tx_sell_swap_pool::set_min_value_to_buy(dev::bigint value) {
    m_min_value_to_buy = std::move(value);
    return *this;
}
