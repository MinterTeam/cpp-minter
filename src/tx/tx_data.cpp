/*!
 * minter_tx.
 * tx_data.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_data.h"

#include "minter/tx/tx.h"

#include <cassert>

minter::tx_data::tx_data(std::shared_ptr<minter::tx> tx)
    : m_tx(std::move(tx)) {
}

std::shared_ptr<minter::tx> minter::tx_data::build() {
    tx()->m_data = encode();
    tx()->m_data_raw = shared_from_this();
    tx()->m_type = type();

    return tx();
}

std::shared_ptr<minter::tx> minter::tx_data::tx() {
    assert(m_tx.get() != nullptr);
    return m_tx;
}
