/*!
 * minter_tx.
 * tx_redeem_check.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_redeem_check.h"
#include "minter/tx/tx_type.h"
minter::tx_redeem_check::tx_redeem_check(std::shared_ptr<minter::tx> tx)
        :tx_data(std::move(tx)) {

}

uint16_t minter::tx_redeem_check::type() const {
    return minter::tx_redeem_check_type::type();
}
dev::bytes minter::tx_redeem_check::encode() {
    dev::RLPStream out;
    dev::RLPStream lst;
    {
        lst.append(m_check);
        lst.append(m_proof);
        out.appendList(lst);
    }

    return out.out();
}

void minter::tx_redeem_check::decode_internal(dev::RLP rlp) {
    m_check = (dev::bytes)rlp[0];
    m_proof = (dev::bytes)rlp[1];
}

minter::tx_redeem_check& minter::tx_redeem_check::set_check(const dev::bytes& data) {
    m_check = data;
    return *this;
}
minter::tx_redeem_check& minter::tx_redeem_check::set_proof(const dev::bytes& data) {
    m_proof = data;
    return *this;
}
const dev::bytes& minter::tx_redeem_check::get_check() const {
    return m_check;
}
const dev::bytes& minter::tx_redeem_check::get_proof() const {
    return m_proof;
}

