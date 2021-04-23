/*!
 * minter_tx.
 * tx_remove_liquidity.cpp.c
 *
 * \date 03/23/2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_remove_liquidity.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

#include <utility>

minter::tx_remove_liquidity::tx_remove_liquidity(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_remove_liquidity::type() const {
    return minter::tx_remove_liquidity_type.type();
}
dev::bytes minter::tx_remove_liquidity::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coin_0);
        lst.append(m_coin_1);
        lst.append(m_liquidity);
        lst.append(m_min_volume_0);
        lst.append(m_min_volume_1);
        out.appendList(lst);
    }
    return out.out();
}
void minter::tx_remove_liquidity::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_coin_0 = minter::utils::to_bigint((dev::bytes) rlp[0]);
    m_coin_1 = minter::utils::to_bigint((dev::bytes) rlp[1]);
    m_liquidity = minter::utils::to_bigint((dev::bytes) rlp[2]);
    m_min_volume_0 = minter::utils::to_bigint((dev::bytes) rlp[3]);
    m_min_volume_1 = minter::utils::to_bigint((dev::bytes) rlp[4]);
}

dev::bigint minter::tx_remove_liquidity::get_coin_0() const {
    return m_coin_0;
}
dev::bigint minter::tx_remove_liquidity::get_coin_1() const {
    return m_coin_1;
}
dev::bigdec18 minter::tx_remove_liquidity::get_liquidity() const {
    return minter::utils::humanize_value(m_liquidity);
}
dev::bigdec18 minter::tx_remove_liquidity::get_min_volume_0() const {
    return minter::utils::humanize_value(m_min_volume_0);
}
dev::bigdec18 minter::tx_remove_liquidity::get_min_volume_1() const {
    return minter::utils::humanize_value(m_min_volume_1);
}

minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_coin_0(dev::bigint coin) {
    m_coin_0 = std::move(coin);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_coin_0(const std::string& coin_id_num) {
    m_coin_0 = dev::bigint(coin_id_num);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_coin_1(dev::bigint coin) {
    m_coin_1 = std::move(coin);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_coin_1(const std::string& coin_id_num) {
    m_coin_1 = dev::bigint(coin_id_num);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_liquidity(const std::string& value) {
    m_liquidity = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_liquidity(const dev::bigdec18& value) {
    m_liquidity = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_liquidity(dev::bigint value) {
    m_liquidity = std::move(value);
    return *this;
}

minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_min_volume_0(const std::string& value) {
    m_min_volume_0 = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_min_volume_0(const dev::bigdec18& value) {
    m_min_volume_0 = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_min_volume_0(dev::bigint value) {
    m_min_volume_0 = std::move(value);
    return *this;
}

minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_min_volume_1(const std::string& value) {
    m_min_volume_1 = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_min_volume_1(const dev::bigdec18& value) {
    m_min_volume_1 = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_remove_liquidity& minter::tx_remove_liquidity::set_min_volume_1(dev::bigint value) {
    m_min_volume_1 = std::move(value);
    return *this;
}
