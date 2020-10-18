//
// Created by edward on 27.08.2020.
//

#include "minter/tx/tx_recreate_coin.h"

#include "minter/tx/tx_type.h"

minter::tx_recreate_coin::tx_recreate_coin(std::shared_ptr<minter::tx> tx)
    : tx_data(tx),
      tx_create_coin(tx) {
}

uint16_t minter::tx_recreate_coin::type() const {
    return minter::tx_type_val::recreate_coin;
}

dev::bytes minter::tx_recreate_coin::encode() {
    return tx_create_coin::encode();
}
void minter::tx_recreate_coin::decode(const dev::bytes& data) {
    tx_create_coin::decode(data);
}

minter::tx_recreate_coin& minter::tx_recreate_coin::set_name(const std::string& coin_name) {
    minter::tx_create_coin::set_name(coin_name);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_ticker(const std::string& coin_symbol) {
    minter::tx_create_coin::set_ticker(coin_symbol);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_initial_amount(const std::string& amount) {
    minter::tx_create_coin::set_initial_amount(amount);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_initial_amount(const dev::bigdec18& amount) {
    minter::tx_create_coin::set_initial_amount(amount);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_initial_amount(const dev::bigint& amount) {
    minter::tx_create_coin::set_initial_amount(amount);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_initial_reserve(const std::string& amount) {
    minter::tx_create_coin::set_initial_reserve(amount);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_initial_reserve(const dev::bigdec18& amount) {
    minter::tx_create_coin::set_initial_reserve(amount);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_initial_reserve(const dev::bigint& amount) {
    minter::tx_create_coin::set_initial_reserve(amount);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_crr(unsigned int crr) {
    minter::tx_create_coin::set_crr(crr);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_max_supply(const std::string& max_supply) {
    minter::tx_create_coin::set_max_supply(max_supply);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_max_supply(const dev::bigint& max_supply) {
    minter::tx_create_coin::set_max_supply(max_supply);
    return *this;
}
minter::tx_recreate_coin& minter::tx_recreate_coin::set_max_supply(const dev::bigdec18& max_supply) {
    minter::tx_create_coin::set_max_supply(max_supply);
    return *this;
}
