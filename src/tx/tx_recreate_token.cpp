/*!
 * minter_tx.
 * tx_recreate_token.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_recreate_token.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

#include <utility>

minter::tx_recreate_token::tx_recreate_token(std::shared_ptr<minter::tx> tx)
    : tx_data(tx),
      tx_create_token(tx) {
}
uint16_t minter::tx_recreate_token::type() const {
    return minter::tx_recreate_token_type.type();
}
dev::bytes minter::tx_recreate_token::encode() {
    return tx_create_token::encode();
}
void minter::tx_recreate_token::decode(const dev::bytes& data) {
    tx_create_token::decode(data);
}
minter::tx_recreate_token& minter::tx_recreate_token::set_name(const std::string& coin_name) {
    tx_create_token::set_name(coin_name);
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_ticker(const std::string& coin_symbol) {
    tx_create_token::set_ticker(coin_symbol);
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_initial_amount(const std::string& amount) {
    tx_create_token::set_initial_amount(amount);
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_initial_amount(const dev::bigdec18& amount) {
    tx_create_token::set_initial_amount(amount);
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_initial_amount(dev::bigint amount) {
    tx_create_token::set_initial_amount(std::move(amount));
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_max_supply(const std::string& max_supply) {
    tx_create_token::set_max_supply(max_supply);
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_max_supply(dev::bigint max_supply) {
    tx_create_token::set_max_supply(std::move(max_supply));
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_max_supply(const dev::bigdec18& max_supply) {
    tx_create_token::set_max_supply(max_supply);
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_mintable(bool mintable) {
    tx_create_token::set_mintable(mintable);
    return *this;
}
minter::tx_recreate_token& minter::tx_recreate_token::set_burnable(bool burnable) {
    tx_create_token::set_burnable(burnable);
    return *this;
}
