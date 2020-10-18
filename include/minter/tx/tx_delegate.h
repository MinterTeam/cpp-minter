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

#include "minter/public_key.h"
#include "tx_data.h"

#include <string>
namespace minter {

class MINTER_TX_API tx_delegate : public virtual minter::tx_data {
public:
    explicit tx_delegate(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_delegate& set_pub_key(const dev::bytes& pub_key);
    tx_delegate& set_pub_key(const minter::pubkey_t& pub_key);
    tx_delegate& set_coin_id(const dev::bigint& coin_id);
    tx_delegate& set_coin_id(const std::string& coin_id_num);
    tx_delegate& set_stake(const std::string& amount);
    tx_delegate& set_stake(const dev::bigint& amount);
    tx_delegate& set_stake(const dev::bigdec18& amount);

    const minter::pubkey_t& get_pub_key() const;
    dev::bigint get_coin_id() const;
    dev::bigdec18 get_stake() const;

private:
    minter::pubkey_t m_pub_key;
    dev::bigint m_coin_id;
    dev::bigint m_stake;
};

} // namespace minter

#endif //MINTER_TX_DELEGATE_H
