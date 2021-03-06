/*!
 * minter_tx.
 * tx_unbound.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_UNBOND_H
#define MINTER_TX_UNBOND_H

#include "minter/public_key.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_unbond : public virtual minter::tx_data {
public:
    explicit tx_unbond(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_unbond& set_pub_key(const minter::pubkey_t& pub_key);
    tx_unbond& set_pub_key(const dev::bytes& pub_key);

    tx_unbond& set_coin_id(dev::bigint coin_id);
    tx_unbond& set_coin_id(const std::string& coin_id_num);

    tx_unbond& set_value(const std::string& value);
    tx_unbond& set_value(const dev::bigdec18& value);
    tx_unbond& set_value(dev::bigint value);

    const minter::pubkey_t& get_pub_key() const;
    dev::bigint get_coin_id() const;
    dev::bigdec18 get_value() const;

private:
    minter::pubkey_t m_pub_key;
    dev::bigint m_coin_id;
    dev::bigint m_value;
};

} // namespace minter

#endif //MINTER_TX_UNBOND_H
