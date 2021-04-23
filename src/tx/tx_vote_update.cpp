/*!
 * minter_tx.
 * tx_vote_update.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include "minter/tx/tx_vote_update.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

#include <utility>

minter::tx_vote_update::tx_vote_update(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_vote_update::type() const {
    return minter::tx_vote_update_type.type();
}

dev::bytes minter::tx_vote_update::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(minter::utils::to_bytes(m_version));
        lst.append(m_pub_key);
        lst.append(m_height);

        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_vote_update::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_version = minter::utils::to_string((dev::bytes) rlp[0]);
    m_pub_key = (dev::bytes) rlp[1];
    m_height = (dev::bigint) rlp[2];
}

std::string minter::tx_vote_update::get_version() const {
    return m_version;
}
const minter::pubkey_t& minter::tx_vote_update::get_pub_key() const {
    return m_pub_key;
}
dev::bigint minter::tx_vote_update::get_height() const {
    return m_height;
}
minter::tx_vote_update& minter::tx_vote_update::set_version(const std::string& version_name) {
    m_version = version_name;
    return *this;
}
minter::tx_vote_update& minter::tx_vote_update::set_pub_key(const minter::pubkey_t& pubkey) {
    m_pub_key = pubkey;
    return *this;
}
minter::tx_vote_update& minter::tx_vote_update::set_pub_key(const std::string& pubkey) {
    m_pub_key = minter::pubkey_t(pubkey);
    return *this;
}
minter::tx_vote_update& minter::tx_vote_update::set_height(dev::bigint height) {
    m_height = std::move(height);
    return *this;
}
minter::tx_vote_update& minter::tx_vote_update::set_height(const std::string& height_num) {
    m_height = dev::bigint(height_num);
    return *this;
}
