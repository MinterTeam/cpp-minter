/*!
 * minter_tx.
 * tx_vote_update.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_VOTE_UPDATE_H
#define MINTER_TX_TX_VOTE_UPDATE_H

#include "minter/public_key.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_vote_update: public virtual minter::tx_data {
public:
    explicit tx_vote_update(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    std::string get_version() const;
    const minter::pubkey_t& get_pub_key() const;
    dev::bigint get_height() const;

    tx_vote_update& set_version(const std::string& version_name);
    tx_vote_update& set_pub_key(const minter::pubkey_t& pubkey);
    tx_vote_update& set_pub_key(const std::string& pubkey);
    tx_vote_update& set_height(dev::bigint height);
    tx_vote_update& set_height(const std::string& height_num);

private:
    std::string m_version;
    minter::pubkey_t m_pub_key;
    dev::bigint m_height;
};

}

#endif //MINTER_TX_TX_VOTE_UPDATE_H
