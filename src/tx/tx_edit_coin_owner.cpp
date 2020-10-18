/*!
 * minter_tx.
 * tx_edit_coin_owner.cpp
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_edit_coin_owner.h"

#include "minter/eth/RLP.h"
#include "minter/tx/utils.h"

minter::tx_edit_coin_owner::tx_edit_coin_owner(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_edit_coin_owner::type() const {
    return minter::tx_edit_coin_owner_type.type();
}

dev::bytes minter::tx_edit_coin_owner::encode() {
    eth::RLPStream out;
    {
        eth::RLPStream lst;
        lst.append(minter::utils::to_bytes_fixed(m_symbol));
        lst.append(m_new_owner.get());

        out.appendList(lst);
    }

    return out.out();
}
void minter::tx_edit_coin_owner::decode(const dev::bytes& data) {
    eth::RLP rlp(data);

    m_symbol = minter::utils::to_string_clear((dev::bytes) rlp[0]);
    m_new_owner = (dev::bytes) rlp[1];
}

minter::tx_edit_coin_owner& minter::tx_edit_coin_owner::set_symbol(const std::string& symbol) {
    m_symbol = symbol;
    return *this;
}
minter::tx_edit_coin_owner& minter::tx_edit_coin_owner::set_symbol(const char* symbol) {
    m_symbol = std::string(symbol);
    return *this;
}
minter::tx_edit_coin_owner& minter::tx_edit_coin_owner::set_new_owner(const minter::address_t& new_owner) {
    m_new_owner = new_owner;
    return *this;
}
std::string minter::tx_edit_coin_owner::get_symbol() const {
    return m_symbol;
}
const minter::address_t& minter::tx_edit_coin_owner::get_new_owner() const {
    return m_new_owner;
}
