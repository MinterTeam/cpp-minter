/*!
 * minter_tx.
 * tx_set_candidate_on_off.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_SET_CANDIDATE_ON_OFF_H
#define MINTER_TX_SET_CANDIDATE_ON_OFF_H

#include "minter/public_key.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_set_candidate_on_off : public virtual minter::tx_data {
public:
    explicit tx_set_candidate_on_off(std::shared_ptr<minter::tx> tx);

    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_set_candidate_on_off& set_pub_key(const dev::bytes& pub_key);
    tx_set_candidate_on_off& set_pub_key(const minter::pubkey_t& pub_key);
    const minter::pubkey_t& get_pub_key() const;

protected:
    minter::pubkey_t m_pub_key;
};

class tx_set_candidate_on : public minter::tx_set_candidate_on_off {
public:
    explicit tx_set_candidate_on(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;
};

class tx_set_candidate_off : public minter::tx_set_candidate_on_off {
public:
    explicit tx_set_candidate_off(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;
};

} // namespace minter

#endif //MINTER_TX_SET_CANDIDATE_ON_OFF_H
