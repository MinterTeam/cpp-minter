/*!
 * minter_tx.
 * tx_declare_candidacy.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_declare_candidacy.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"
minter::tx_declare_candidacy::tx_declare_candidacy(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
uint16_t minter::tx_declare_candidacy::type() const {
    return minter::tx_declare_candidacy_type.type();
}
dev::bytes minter::tx_declare_candidacy::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_address.get());
        lst.append(m_pub_key.get());
        lst.append(m_commission);
        lst.append(m_coin_id);
        lst.append(m_stake);

        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_declare_candidacy::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_address = (dev::bytes) rlp[0];
    m_pub_key = (dev::bytes) rlp[1];
    m_commission = (dev::bigint) rlp[2];
    m_coin_id = (dev::bigint) rlp[3];
    m_stake = (dev::bigint) rlp[4];
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_address(const minter::data::address& address) {
    m_address = address;
    return *this;
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_pub_key(const minter::pubkey_t& pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_pub_key(const dev::bytes& pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_commission(unsigned commission) {
    m_commission = dev::bigint(commission);
    return *this;
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_coin_id(const dev::bigint& coin_id) {
    m_coin_id = coin_id;
    return *this;
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_coin_id(const std::string& coin_id_num) {
    m_coin_id = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_stake(const std::string& amount) {
    m_stake = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_stake(const dev::bigint& amount) {
    m_stake = amount;
    return *this;
}

minter::tx_declare_candidacy& minter::tx_declare_candidacy::set_stake(const dev::bigdec18& amount) {
    m_stake = minter::utils::normalize_value(amount);
    return *this;
}

const minter::data::address& minter::tx_declare_candidacy::get_address() const {
    return m_address;
}

const minter::pubkey_t& minter::tx_declare_candidacy::get_pub_key() const {
    return m_pub_key;
}

unsigned minter::tx_declare_candidacy::get_commission() const {
    return static_cast<unsigned>(m_commission);
}

dev::bigint minter::tx_declare_candidacy::get_coin_id() const {
    return m_coin_id;
}

dev::bigdec18 minter::tx_declare_candidacy::get_stake() const {
    return minter::utils::humanize_value(m_stake);
}
