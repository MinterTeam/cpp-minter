/*!
 * minter_tx.
 * tx_delegate.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_DELEGATE_H
#define MINTER_TX_DELEGATE_H

#include <string>
#include "minter/public_key.h"
#include "tx_data.h"
namespace minter {

class tx_delegate: public virtual minter::tx_data {
public:
    explicit tx_delegate(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;

    tx_delegate& set_pub_key(const dev::bytes &pub_key);
    tx_delegate& set_pub_key(const minter::pubkey_t &pub_key);
    tx_delegate& set_coin(const char* coin);
    tx_delegate& set_coin(const std::string &coin);
    tx_delegate& set_stake(const char* amount);
    tx_delegate& set_stake(const dev::bigdec18 &amount);

    const minter::pubkey_t& get_pub_key() const;
    std::string get_coin() const;
    dev::bigdec18 get_stake() const;

protected:
    void decode_internal(dev::RLP rlp) override;

private:
    minter::pubkey_t m_pub_key;
    std::string m_coin;
    dev::bigint m_stake;
};

}

#endif //MINTER_TX_DELEGATE_H
