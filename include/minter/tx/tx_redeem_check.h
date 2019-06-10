/*!
 * minter_tx.
 * tx_redeem_check.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_REDEEM_CHECK_H
#define MINTER_TX_REDEEM_CHECK_H

#include "tx_data.h"
namespace minter {

static const uint32_t PROOF_LEN = 65;

class tx_redeem_check: public virtual minter::tx_data {
public:
    explicit tx_redeem_check(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;

    tx_redeem_check& set_check(const dev::bytes &data);
    tx_redeem_check& set_proof(const dev::bytes &data);

    const dev::bytes get_check() const;
    const dev::bytes get_proof() const;

protected:
    void decode_internal(dev::RLP rlp) override;

private:
    dev::bytes m_check;
    dev::bytes m_proof;
};

}

#endif //MINTER_TX_REDEEM_CHECK_H
