/*!
 * minter_tx.
 * tx_create_swap_pool.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_create_swap_pool.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

minter::tx_create_swap_pool::tx_create_swap_pool(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_create_swap_pool::type() const {
    return minter::tx_create_swap_pool_type.type();
}
dev::bytes minter::tx_create_swap_pool::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coin_0);
        lst.append(m_coin_1);
        lst.append(m_volume_0);
        lst.append(m_volume_1);
        out.appendList(lst);
    }
    return out.out();
}
void minter::tx_create_swap_pool::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_coin_0 = minter::utils::to_bigint((dev::bytes) rlp[0]);
    m_coin_1 = minter::utils::to_bigint((dev::bytes) rlp[1]);
    m_volume_0 = minter::utils::to_bigint((dev::bytes) rlp[2]);
    m_volume_1 = minter::utils::to_bigint((dev::bytes) rlp[3]);
}

dev::bigint minter::tx_create_swap_pool::get_coin_0() const {
    return m_coin_0;
}
dev::bigint minter::tx_create_swap_pool::get_coin_1() const {
    return m_coin_1;
}
dev::bigdec18 minter::tx_create_swap_pool::get_volume_0() const {
    return minter::utils::humanize_value(m_volume_0);
}
dev::bigdec18 minter::tx_create_swap_pool::get_volume_1() const {
    return minter::utils::humanize_value(m_volume_1);
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_coin_0(dev::bigint coin) {
    m_coin_0 = std::move(coin);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_coin_0(const std::string& coin_id_num) {
    m_coin_0 = dev::bigint(coin_id_num);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_coin_1(dev::bigint coin) {
    m_coin_1 = std::move(coin);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_coin_1(const std::string& coin_id_num) {
    m_coin_1 = dev::bigint(coin_id_num);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_volume_0(const std::string& volume) {
    m_volume_0 = minter::utils::normalize_value(volume);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_volume_0(dev::bigint volume) {
    m_volume_0 = std::move(volume);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_volume_0(const dev::bigdec18& volume) {
    m_volume_0 = minter::utils::normalize_value(volume);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_volume_1(const std::string& volume) {
    m_volume_1 = minter::utils::normalize_value(volume);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_volume_1(dev::bigint volume) {
    m_volume_1 = std::move(volume);
    return *this;
}
minter::tx_create_swap_pool& minter::tx_create_swap_pool::set_volume_1(const dev::bigdec18& volume) {
    m_volume_1 = minter::utils::normalize_value(volume);
    return *this;
}
