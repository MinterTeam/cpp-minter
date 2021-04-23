/*!
 * minter_tx.
 * tx_edit_candidate_commission.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_EDIT_CANDIDATE_COMMISSION_H
#define MINTER_TX_TX_EDIT_CANDIDATE_COMMISSION_H

#include "minter/public_key.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_edit_candidate_commission : public virtual minter::tx_data {
public:
    explicit tx_edit_candidate_commission(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    const minter::pubkey_t& get_pub_key() const;
    uint32_t get_commission() const;

    tx_edit_candidate_commission& set_pub_key(const minter::pubkey_t& pubkey);
    tx_edit_candidate_commission& set_commission(uint32_t commission);

private:
    minter::pubkey_t m_pub_key;
    dev::bigint m_commission;
};

} // namespace minter

#endif //MINTER_TX_TX_EDIT_CANDIDATE_COMMISSION_H
