/*!
 * minter_tx.
 * tx_declare_candidacy.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_DECLARE_CANDIDACY_H
#define MINTER_TX_DECLARE_CANDIDACY_H

#include "minter/address.h"
#include "minter/public_key.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_declare_candidacy : public virtual minter::tx_data {
public:
    explicit tx_declare_candidacy(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_declare_candidacy& set_address(const minter::address_t& address);
    tx_declare_candidacy& set_pub_key(const minter::pubkey_t& pub_key);
    tx_declare_candidacy& set_pub_key(const dev::bytes& pub_key);
    /// validator reward
    /// \param commission from 10 to 100 percent
    /// \return
    tx_declare_candidacy& set_commission(unsigned commission);
    tx_declare_candidacy& set_coin_id(dev::bigint coin_id);
    tx_declare_candidacy& set_coin_id(const std::string& coin_id_num);
    tx_declare_candidacy& set_stake(const std::string& amount);
    tx_declare_candidacy& set_stake(dev::bigint amount);
    tx_declare_candidacy& set_stake(const dev::bigdec18& amount);

    const minter::address_t& get_address() const;
    const minter::pubkey_t& get_pub_key() const;
    unsigned get_commission() const;
    dev::bigint get_coin_id() const;
    dev::bigdec18 get_stake() const;

private:
    minter::data::address m_address;
    minter::pubkey_t m_pub_key;
    dev::bigint m_commission;
    dev::bigint m_coin_id;
    dev::bigint m_stake;
};

} // namespace minter

#endif //MINTER_TX_DECLARE_CANDIDACY_H
