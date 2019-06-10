/*!
 * minter_tx.
 * tx_set_candidate_on_off.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_type.h"
#include "minter/tx/tx_set_candidate_on_off.h"
#include "minter/tx/tx_type.h"

// BASE
minter::tx_set_candidate_on_off::tx_set_candidate_on_off(std::shared_ptr<minter::tx> tx) : tx_data(std::move(tx)) {

}

dev::bytes minter::tx_set_candidate_on_off::encode() {
    dev::RLPStream out;
    dev::RLPStream lst;
    {
        lst.append((dev::bytes)m_pub_key);
        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_set_candidate_on_off::decode_internal(dev::RLP rlp) {
    m_pub_key = (dev::bytes)rlp[0];
}

minter::tx_set_candidate_on_off& minter::tx_set_candidate_on_off::set_pub_key(const dev::bytes& pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_set_candidate_on_off& minter::tx_set_candidate_on_off::set_pub_key(const minter::pubkey_t &pub_key) {
    m_pub_key = pub_key;
    return *this;
}

const minter::pubkey_t& minter::tx_set_candidate_on_off::get_pub_key() const {
    return m_pub_key;
}

// ON
uint16_t minter::tx_set_candidate_on::type() const {
    return minter::tx_set_candidate_on_type::type();
}
minter::tx_set_candidate_on::tx_set_candidate_on(std::shared_ptr<minter::tx> tx) : tx_set_candidate_on_off(tx), tx_data(tx) {

}
void minter::tx_set_candidate_on::decode_internal(dev::RLP rlp) {
    tx_set_candidate_on_off::decode_internal(rlp);
}
dev::bytes minter::tx_set_candidate_on::encode() {
    return tx_set_candidate_on_off::encode();
}

// OFF

uint16_t minter::tx_set_candidate_off::type() const {
    return minter::tx_set_candidate_off_type::type();
}
minter::tx_set_candidate_off::tx_set_candidate_off(std::shared_ptr<minter::tx> tx) : tx_set_candidate_on_off(tx), tx_data(tx) {

}
void minter::tx_set_candidate_off::decode_internal(dev::RLP rlp) {
    tx_set_candidate_on_off::decode_internal(rlp);
}

dev::bytes minter::tx_set_candidate_off::encode() {
    return tx_set_candidate_on_off::encode();
}
