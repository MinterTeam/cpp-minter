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
#include "tx_data.h"
#include "minter/public_key.h"
namespace minter {

class MINTER_TX_API tx_unbond: public virtual minter::tx_data {
public:
    explicit tx_unbond(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;

    tx_unbond& set_pub_key(const minter::pubkey_t &pub_key);
    tx_unbond& set_pub_key(const dev::bytes &pub_key);
    tx_unbond& set_coin(const char* coin);
    tx_unbond& set_coin(const std::string &coin);
    tx_unbond& set_value(const char* value);
    tx_unbond& set_value(const dev::bigdec18 &value);

    const minter::pubkey_t& get_pub_key() const;
    std::string get_coin() const;
    dev::bigdec18 get_value() const;

protected:
    void decode_internal(dev::RLP rlp) override;

private:
    minter::pubkey_t m_pub_key;
    std::string m_coin;
    dev::bigint m_value;
};

}

#endif //MINTER_TX_UNBOND_H
