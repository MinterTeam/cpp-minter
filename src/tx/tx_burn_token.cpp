/*!
 * minter_tx.
 * tx_burn_token.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include "minter/tx/tx_burn_token.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

#include <utility>

minter::tx_burn_token::tx_burn_token(std::shared_ptr<minter::tx> tx)
    : tx_data(tx),
      minter::tx_mint_token(tx) {
}
uint16_t minter::tx_burn_token::type() const {
    return minter::tx_burn_token_type.type();
}
dev::bytes minter::tx_burn_token::encode() {
    return tx_mint_token::encode();
}
void minter::tx_burn_token::decode(const dev::bytes& data) {
    tx_mint_token::decode(data);
}

minter::tx_burn_token& minter::tx_burn_token::set_coin_id(dev::bigint coin) {
    tx_mint_token::set_coin_id(std::move(coin));
    return *this;
}
minter::tx_burn_token& minter::tx_burn_token::set_coin_id(const std::string& coin_id_num) {
    tx_mint_token::set_coin_id(coin_id_num);
    return *this;
}
minter::tx_burn_token& minter::tx_burn_token::set_value(const std::string& value) {
    tx_mint_token::set_value(value);
    return *this;
}
minter::tx_burn_token& minter::tx_burn_token::set_value(const dev::bigdec18& value) {
    tx_mint_token::set_value(value);
    return *this;
}
minter::tx_burn_token& minter::tx_burn_token::set_value(dev::bigint value) {
    tx_mint_token::set_value(std::move(value));
    return *this;
}
