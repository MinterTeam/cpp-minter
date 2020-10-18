/*!
 * minter_tx.
 * tx_edit_candidate_public_key.cpp
 *
 * \date 09/16/2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_edit_candidate_public_key.h"

#include "minter/eth/RLP.h"
#include "minter/tx/tx_type.h"

minter::tx_edit_candidate_public_key::tx_edit_candidate_public_key(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_edit_candidate_public_key::type() const {
    return minter::tx_edit_candidate_public_key_type.type();
}
dev::bytes minter::tx_edit_candidate_public_key::encode() {
    eth::RLPStream out;
    {
        eth::RLPStream list;
        list.append(m_pub_key);
        list.append(m_new_pub_key);

        out.appendList(list);
    }

    return out.out();
}
void minter::tx_edit_candidate_public_key::decode(const dev::bytes& data) {

    eth::RLP s(data);
    m_pub_key = (dev::bytes) s[0];
    m_new_pub_key = (dev::bytes) s[1];
}

minter::tx_edit_candidate_public_key& minter::tx_edit_candidate_public_key::set_public_key(const minter::pubkey_t& pubkey) {
    m_pub_key = pubkey;
    return *this;
}
minter::tx_edit_candidate_public_key& minter::tx_edit_candidate_public_key::set_public_key(const std::string& pubkey) {
    m_pub_key = minter::pubkey_t(pubkey);
    return *this;
}
minter::tx_edit_candidate_public_key& minter::tx_edit_candidate_public_key::set_new_public_key(const minter::pubkey_t& pubkey) {
    m_new_pub_key = pubkey;
    return *this;
}
minter::tx_edit_candidate_public_key& minter::tx_edit_candidate_public_key::set_new_public_key(const std::string& pubkey) {
    m_new_pub_key = minter::pubkey_t(pubkey);
    return *this;
}
const minter::pubkey_t& minter::tx_edit_candidate_public_key::get_public_key() const {
    return m_pub_key;
}
const minter::pubkey_t& minter::tx_edit_candidate_public_key::get_new_public_key() const {
    return m_new_pub_key;
}
