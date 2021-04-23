/*!
 * minter_tx.
 * tx_create_token.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include "minter/tx/tx_create_token.h"

#include <utility>

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

minter::tx_create_token::tx_create_token(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)),
      m_max_supply(minter::utils::normalize_value(dev::bigdec18("1000000000000000"))),
      m_mintable("1"),
      m_burnable("1") {
}

uint16_t minter::tx_create_token::type() const {
    return minter::tx_create_token_type.type();
}
dev::bytes minter::tx_create_token::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(minter::utils::to_bytes(m_name));
        lst.append(minter::utils::to_bytes_fixed(m_ticker));
        lst.append(m_initial_amount);
        lst.append(m_max_supply);
        lst.append(m_mintable);
        lst.append(m_burnable);

        out.appendList(lst);
    }

    return out.out();
}
void minter::tx_create_token::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_name = minter::utils::to_string((dev::bytes) rlp[0]);
    m_ticker = minter::utils::to_string_clear((dev::bytes) rlp[1]);
    m_initial_amount = (dev::bigint) rlp[2];
    m_max_supply = (dev::bigint) rlp[3];
    m_mintable = (dev::bigint) rlp[4];
    m_burnable = (dev::bigint) rlp[5];
}

std::string minter::tx_create_token::get_name() const {
    return m_name;
}
std::string minter::tx_create_token::get_ticker() const {
    return m_ticker;
}
dev::bigdec18 minter::tx_create_token::get_initial_amount() const {
    return minter::utils::humanize_value(m_initial_amount);
}
dev::bigdec18 minter::tx_create_token::get_max_supply() const {
    return minter::utils::humanize_value(m_max_supply);
}
bool minter::tx_create_token::is_mintable() const {
    return m_mintable == dev::bigint("1");
}
bool minter::tx_create_token::is_burnable() const {
    return m_burnable == dev::bigint("1");
}

minter::tx_create_token& minter::tx_create_token::set_name(const std::string& name) {
    m_name = name;
    return *this;
}

minter::tx_create_token& minter::tx_create_token::set_ticker(const std::string& coin_symbol) {
    m_ticker = coin_symbol;
    return *this;
}

minter::tx_create_token& minter::tx_create_token::set_initial_amount(const std::string& amount) {
    m_initial_amount = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_create_token& minter::tx_create_token::set_initial_amount(const dev::bigdec18& amount) {
    m_initial_amount = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_create_token& minter::tx_create_token::set_initial_amount(dev::bigint amount) {
    m_initial_amount = std::move(amount);
    return *this;
}

minter::tx_create_token& minter::tx_create_token::set_max_supply(const std::string& max_supply) {
    m_max_supply = minter::utils::normalize_value(max_supply);
    return *this;
}
minter::tx_create_token& minter::tx_create_token::set_max_supply(dev::bigint max_supply) {
    m_max_supply = std::move(max_supply);
    return *this;
}
minter::tx_create_token& minter::tx_create_token::set_max_supply(const dev::bigdec18& max_supply) {
    m_max_supply = minter::utils::normalize_value(max_supply);
    return *this;
}

minter::tx_create_token& minter::tx_create_token::set_mintable(bool mintable) {
    m_mintable = mintable ? dev::bigint("1") : dev::bigint("0");
    return *this;
}
minter::tx_create_token& minter::tx_create_token::set_burnable(bool burnable) {
    m_burnable = burnable ? dev::bigint("1") : dev::bigint("0");
    return *this;
}
