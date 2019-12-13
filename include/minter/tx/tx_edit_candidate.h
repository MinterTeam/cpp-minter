/*!
 * minter_tx.
 * tx_edit_candidate.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_EDIT_CANDIDATE_H
#define MINTER_TX_EDIT_CANDIDATE_H

#include "minter/address.h"
#include "minter/public_key.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_edit_candidate : public virtual minter::tx_data {
public:
    explicit tx_edit_candidate(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_edit_candidate& set_pub_key(const minter::pubkey_t& pub_key);
    tx_edit_candidate& set_pub_key(const dev::bytes& pub_key);
    tx_edit_candidate& set_reward_address(const minter::address_t& address);
    tx_edit_candidate& set_owner_address(const minter::address_t& address);

    const minter::pubkey_t& get_pub_key() const;
    const minter::data::address& get_reward_address() const;
    const minter::data::address& get_owner_address() const;

private:
    minter::pubkey_t m_pub_key;
    minter::data::address m_reward_address;
    minter::data::address m_owner_address;
};

} // namespace minter

#endif //MINTER_TX_EDIT_CANDIDATE_H
