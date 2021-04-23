/*!
 * minter_tx.
 * tx_mint_token.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include "minter/tx/tx_mint_token.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

#include <utility>

minter::tx_mint_token::tx_mint_token(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_mint_token::type() const {
    return minter::tx_mint_token_type.type();
}
dev::bytes minter::tx_mint_token::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_coin_id);
        lst.append(m_value);
        out.appendList(lst);
    }
    return out.out();
}
void minter::tx_mint_token::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_coin_id = minter::utils::to_bigint((dev::bytes) rlp[0]);
    m_value = minter::utils::to_bigint((dev::bytes) rlp[1]);
}

dev::bigint minter::tx_mint_token::get_coin_id() const {
    return m_coin_id;
}
dev::bigdec18 minter::tx_mint_token::get_value() const {
    return minter::utils::humanize_value(m_value);
}
minter::tx_mint_token& minter::tx_mint_token::set_coin_id(dev::bigint coin) {
    m_coin_id = std::move(coin);
    return *this;
}
minter::tx_mint_token& minter::tx_mint_token::set_coin_id(const std::string& coin_id_num) {
    m_coin_id = dev::bigint(coin_id_num);
    return *this;
}
minter::tx_mint_token& minter::tx_mint_token::set_value(const std::string& value) {
    m_value = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_mint_token& minter::tx_mint_token::set_value(const dev::bigdec18& value) {
    m_value = minter::utils::normalize_value(value);
    return *this;
}
minter::tx_mint_token& minter::tx_mint_token::set_value(dev::bigint value) {
    m_value = std::move(value);
    return *this;
}
