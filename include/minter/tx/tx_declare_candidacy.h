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

#include "tx_data.h"
#include "minter/public_key.h"

namespace minter {

class MINTER_TX_API tx_declare_candidacy: public virtual minter::tx_data {
public:
    explicit tx_declare_candidacy(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;


    tx_declare_candidacy& set_address(const minter::data::address &address);
    tx_declare_candidacy& set_pub_key(const minter::pubkey_t &pub_key);
    tx_declare_candidacy& set_pub_key(const dev::bytes &pub_key);
    /// validator reward
    /// \param commission from 10 to 100 percent
    /// \return
    tx_declare_candidacy& set_commission(unsigned commission);
    tx_declare_candidacy& set_coin(const char* coin);
    tx_declare_candidacy& set_stake(const char* amount);
    tx_declare_candidacy& set_stake(const dev::bigdec18 &amount);

    const minter::data::address& get_address() const;
    const minter::pubkey_t& get_pub_key() const;
    unsigned get_commission() const;
    std::string get_coin() const;
    dev::bigdec18 get_stake() const;


protected:
    void decode_internal(dev::RLP rlp) override;

private:
    minter::data::address m_address;
    minter::pubkey_t m_pub_key;
    dev::bigint m_commission;
    std::string m_coin;
    dev::bigint m_stake;
};

}

#endif //MINTER_TX_DECLARE_CANDIDACY_H
