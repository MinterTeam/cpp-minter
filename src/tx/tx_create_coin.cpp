/*!
 * minter_tx.
 * tx_create_coin.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_create_coin.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

minter::tx_create_coin::tx_create_coin(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)),
      m_max_supply(minter::utils::normalize_value(dev::bigdec18("1000000000000000"))) {
}

uint16_t minter::tx_create_coin::type() const {
    return minter::tx_create_coin_type.type();
}
dev::bytes minter::tx_create_coin::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(minter::utils::to_bytes(m_name));
        lst.append(minter::utils::to_bytes_fixed(m_ticker));
        lst.append(m_initial_amount);
        lst.append(m_initial_reserve);
        lst.append(m_crr);
        lst.append(m_max_supply);

        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_create_coin::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_name = minter::utils::to_string((dev::bytes) rlp[0]);
    m_ticker = minter::utils::to_string_clear((dev::bytes) rlp[1]);
    m_initial_amount = (dev::bigint) rlp[2];
    m_initial_reserve = (dev::bigint) rlp[3];
    m_crr = (dev::bigint) rlp[4];
    m_max_supply = (dev::bigint) rlp[5];
}

minter::tx_create_coin& minter::tx_create_coin::set_name(const std::string& name) {
    m_name = name;
    return *this;
}

minter::tx_create_coin& minter::tx_create_coin::set_ticker(const std::string& coin_symbol) {
    m_ticker = coin_symbol;
    return *this;
}

minter::tx_create_coin& minter::tx_create_coin::set_initial_amount(const std::string& amount) {
    m_initial_amount = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_create_coin& minter::tx_create_coin::set_initial_amount(const dev::bigdec18& amount) {
    m_initial_amount = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_create_coin& minter::tx_create_coin::set_initial_amount(const dev::bigint& amount) {
    m_initial_amount = amount;
    return *this;
}

minter::tx_create_coin& minter::tx_create_coin::set_initial_reserve(const std::string& amount) {
    m_initial_reserve = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_create_coin& minter::tx_create_coin::set_initial_reserve(const dev::bigdec18& amount) {
    m_initial_reserve = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_create_coin& minter::tx_create_coin::set_initial_reserve(const dev::bigint& amount) {
    m_initial_reserve = amount;
    return *this;
}

minter::tx_create_coin& minter::tx_create_coin::set_crr(unsigned crr) {
    if (crr > 100) {
        throw std::runtime_error("maximum crr: 100 (means 100%)");
    }
    m_crr = dev::bigint(crr);
    return *this;
}

std::string minter::tx_create_coin::get_name() const {
    return m_name;
}

std::string minter::tx_create_coin::get_ticker() const {
    return m_ticker;
}

dev::bigdec18 minter::tx_create_coin::get_initial_amount() const {
    return minter::utils::humanize_value(m_initial_amount);
}

dev::bigdec18 minter::tx_create_coin::get_initial_reserve() const {
    return minter::utils::humanize_value(m_initial_reserve);
}

unsigned minter::tx_create_coin::get_crr() const {
    return static_cast<unsigned>(m_crr);
}

minter::tx_create_coin& minter::tx_create_coin::set_max_supply(const std::string& max_supply) {
    m_max_supply = minter::utils::normalize_value(max_supply);
    return *this;
}
minter::tx_create_coin& minter::tx_create_coin::set_max_supply(const dev::bigint& max_supply) {
    m_max_supply = max_supply;
    return *this;
}
minter::tx_create_coin& minter::tx_create_coin::set_max_supply(const dev::bigdec18& max_supply) {
    m_max_supply = minter::utils::normalize_value(max_supply);
    return *this;
}
dev::bigdec18 minter::tx_create_coin::get_max_supply() const {
    return minter::utils::humanize_value(m_max_supply);
}
