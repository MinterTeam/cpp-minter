/*!
 * minter_tx.
 * tx_edit_candidate_commission.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_edit_candidate_commission.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

minter::tx_edit_candidate_commission::tx_edit_candidate_commission(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
uint16_t minter::tx_edit_candidate_commission::type() const {
    return minter::tx_edit_candidate_commission_type.type();
}
dev::bytes minter::tx_edit_candidate_commission::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_pub_key);
        lst.append(m_commission);
        out.appendList(lst);
    }
    return out.out();
}
void minter::tx_edit_candidate_commission::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_pub_key = (dev::bytes) rlp[0];
    m_commission = minter::utils::to_bigint((dev::bytes) rlp[1]);
}

const minter::pubkey_t& minter::tx_edit_candidate_commission::get_pub_key() const {
    return m_pub_key;
}
uint32_t minter::tx_edit_candidate_commission::get_commission() const {
    return (uint32_t) m_commission;
}
minter::tx_edit_candidate_commission& minter::tx_edit_candidate_commission::set_pub_key(const minter::pubkey_t& pubkey) {
    m_pub_key = pubkey;
    return *this;
}
minter::tx_edit_candidate_commission& minter::tx_edit_candidate_commission::set_commission(uint32_t commission) {
    m_commission = commission;
    return *this;
}
