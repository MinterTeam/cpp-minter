/*!
 * minter_tx.
 * tx_add_liquidity.cpp.c
 *
 * \date 03/23/2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_add_liquidity.h"

#include <utility>
#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

minter::tx_add_liquidity::tx_add_liquidity(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_add_liquidity::type() const {
    return minter::tx_add_liquidity_type.type();
}
dev::bytes minter::tx_add_liquidity::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coin_0);
        lst.append(m_coin_1);
        lst.append(m_volume_0);
        lst.append(m_max_volume_1);
        out.appendList(lst);
    }
    return out.out();
}
void minter::tx_add_liquidity::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_coin_0 = minter::utils::to_bigint((dev::bytes) rlp[0]);
    m_coin_1 = minter::utils::to_bigint((dev::bytes) rlp[1]);
    m_volume_0 = minter::utils::to_bigint((dev::bytes) rlp[2]);
    m_max_volume_1 = minter::utils::to_bigint((dev::bytes) rlp[3]);
}

dev::bigint minter::tx_add_liquidity::get_coin_0() const {
    return m_coin_0;
}
dev::bigint minter::tx_add_liquidity::get_coin_1() const {
    return m_coin_1;
}
dev::bigdec18 minter::tx_add_liquidity::get_volume_0() const {
    return minter::utils::humanize_value(m_volume_0);
}
dev::bigdec18 minter::tx_add_liquidity::get_max_volume_1() const {
    return minter::utils::humanize_value(m_max_volume_1);
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_coin_0(dev::bigint coin) {
    m_coin_0 = std::move(coin);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_coin_0(const std::string& coin_id_num) {
    m_coin_0 = dev::bigint(coin_id_num);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_coin_1(dev::bigint coin) {
    m_coin_1 = std::move(coin);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_coin_1(const std::string& coin_id_num) {
    m_coin_1 = dev::bigint(coin_id_num);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_volume_0(const std::string& value) {
    m_volume_0 = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_volume_0(const dev::bigdec18& value) {
    m_volume_0 = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_volume_0(dev::bigint value) {
    m_volume_0 = std::move(value);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_max_volume_1(const std::string& value) {
    m_max_volume_1 = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_max_volume_1(const dev::bigdec18& value) {
    m_max_volume_1 = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_add_liquidity& minter::tx_add_liquidity::set_max_volume_1(dev::bigint value) {
    m_max_volume_1 = std::move(value);
    return *this;
}
