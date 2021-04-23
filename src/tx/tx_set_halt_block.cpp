/*!
 * minter_tx.
 * tx_set_halt_block.cpp
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_set_halt_block.h"

#include <utility>

#include "minter/tx/tx_type.h"

minter::tx_set_halt_block::tx_set_halt_block(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
uint16_t minter::tx_set_halt_block::type() const {
    return minter::tx_type_val::set_halt_block;
}
dev::bytes minter::tx_set_halt_block::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_public_key.get());
        lst.append(m_height);

        out.appendList(lst);
    }

    return out.out();
}
void minter::tx_set_halt_block::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_public_key = (dev::bytes) rlp[0];
    m_height = (dev::bigint) rlp[1];
}

minter::tx_set_halt_block& minter::tx_set_halt_block::set_public_key(const minter::pubkey_t& public_key) {
    m_public_key = public_key;
    return *this;
}

minter::tx_set_halt_block& minter::tx_set_halt_block::set_public_key(const dev::bytes& public_key_bytes) {
    m_public_key = public_key_bytes;
    return *this;
}

minter::tx_set_halt_block& minter::tx_set_halt_block::set_height(const std::string& height_num) {
    m_height = dev::bigint(height_num);
    return *this;
}

minter::tx_set_halt_block& minter::tx_set_halt_block::set_height(dev::bigint height) {
    m_height = std::move(height);
    return *this;
}
const minter::pubkey_t& minter::tx_set_halt_block::get_public_key() const {
    return m_public_key;
}
dev::bigint minter::tx_set_halt_block::get_height() const {
    return m_height;
}
