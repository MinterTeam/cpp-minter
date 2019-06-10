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
minter::tx_declare_candidacy::tx_declare_candidacy(std::shared_ptr<minter::tx> tx) : tx_data(std::move(tx)) {

}
uint16_t minter::tx_declare_candidacy::type() const {
    return minter::tx_declare_candidacy_type::type();
}
dev::bytes minter::tx_declare_candidacy::encode() {
    dev::RLPStream out;
    dev::RLPStream lst;
    {
        lst.append(m_address.get());
        lst.append((dev::bytes)m_pub_key);
        lst.append(m_commission);
        lst.append(minter::utils::to_bytes_fixed(m_coin, 10));
        lst.append(m_stake);

        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_declare_candidacy::decode_internal(dev::RLP rlp) {
    m_address = (dev::bytes)rlp[0];
    m_pub_key = (dev::bytes)rlp[1];
    m_commission = (dev::bigint)rlp[2];
    m_coin = minter::utils::to_string_clear((dev::bytes)rlp[3]);
    m_stake = (dev::bigint)rlp[4];
}

minter::tx_declare_candidacy &minter::tx_declare_candidacy::set_address(const minter::data::address &address) {
    m_address = address;
    return *this;
}

minter::tx_declare_candidacy &minter::tx_declare_candidacy::set_pub_key(const minter::pubkey_t &pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_declare_candidacy &minter::tx_declare_candidacy::set_pub_key(const dev::bytes &pub_key) {
    m_pub_key = pub_key;
    return *this;
}

minter::tx_declare_candidacy &minter::tx_declare_candidacy::set_commission(unsigned commission) {
    m_commission = dev::bigint(commission);
    return *this;
}

minter::tx_declare_candidacy &minter::tx_declare_candidacy::set_coin(const char *coin) {
    m_coin = std::string(coin);
    return *this;
}

minter::tx_declare_candidacy &minter::tx_declare_candidacy::set_stake(const char *amount) {
    m_stake = minter::utils::normalize_value(amount);
    return *this;
}

minter::tx_declare_candidacy &minter::tx_declare_candidacy::set_stake(const dev::bigdec18 &amount) {
    m_stake = minter::utils::normalize_value(amount);
    return *this;
}

const minter::data::address &minter::tx_declare_candidacy::get_address() const {
    return m_address;
}

const minter::pubkey_t& minter::tx_declare_candidacy::get_pub_key() const {
    return m_pub_key;
}

unsigned minter::tx_declare_candidacy::get_commission() const {
    return static_cast<unsigned>(m_commission);
}

std::string minter::tx_declare_candidacy::get_coin() const {
    return m_coin;
}

dev::bigdec18 minter::tx_declare_candidacy::get_stake() const {
    return minter::utils::humanize_value(m_stake);
}

