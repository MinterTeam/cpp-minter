/*!
 * minter_tx.
 * tx_redeem_check.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_REDEEM_CHECK_H
#define MINTER_TX_REDEEM_CHECK_H

#include "minter/check.h"
#include "tx_data.h"
namespace minter {

class MINTER_TX_API tx_redeem_check : public virtual minter::tx_data {
public:
    explicit tx_redeem_check(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_redeem_check& set_check(const dev::bytes& check_data);
    tx_redeem_check& set_check(const dev::bytes_data& check_data);
    tx_redeem_check& set_check(const check_t& check_data);
    tx_redeem_check& set_proof(const dev::bytes& proof);
    tx_redeem_check& set_proof(const dev::bytes_data& proof);

    const dev::bytes& get_check() const;
    const dev::bytes& get_proof() const;

private:
    dev::bytes m_check;
    dev::bytes m_proof;
};

} // namespace minter

#endif //MINTER_TX_REDEEM_CHECK_H
