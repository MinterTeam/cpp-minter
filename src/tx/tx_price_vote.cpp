/*!
 * minter_tx.
 * tx_price_vote.cpp
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_price_vote.h"

#include "minter/tx/tx_type.h"

minter::tx_price_vote::tx_price_vote(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_price_vote::type() const {
    return minter::tx_price_vote_type.type();
}
dev::bytes minter::tx_price_vote::encode() {
    return dev::bytes();
}
void minter::tx_price_vote::decode(const dev::bytes& data) {
}

minter::tx_price_vote& minter::tx_price_vote::set_price(dev::bigint price) {
    m_price = std::move(price);
    return *this;
}

dev::bigint minter::tx_price_vote::get_price() const {
    return m_price;
}
