/*!
 * minter_tx.
 * tx_edit_candidate_public_key.h
 *
 * \date 09/16/2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#ifndef MINTER_TX_TX_EDIT_CANDIDATE_PUBLIC_KEY_H
#define MINTER_TX_TX_EDIT_CANDIDATE_PUBLIC_KEY_H

#include "minter/public_key.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_edit_candidate_public_key : public virtual minter::tx_data {
public:
    explicit tx_edit_candidate_public_key(std::shared_ptr<minter::tx> tx);

    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_edit_candidate_public_key& set_public_key(const minter::pubkey_t& pubkey);
    tx_edit_candidate_public_key& set_public_key(const std::string& pubkey);
    tx_edit_candidate_public_key& set_new_public_key(const minter::pubkey_t& pubkey);
    tx_edit_candidate_public_key& set_new_public_key(const std::string& pubkey);

    const minter::pubkey_t& get_public_key() const;
    const minter::pubkey_t& get_new_public_key() const;

private:
    minter::pubkey_t m_pub_key;
    minter::pubkey_t m_new_pub_key;
};

} // namespace minter

#endif //MINTER_TX_TX_EDIT_CANDIDATE_PUBLIC_KEY_H
