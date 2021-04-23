/*!
 * minter_tx.
 * tx_set_halt_block.h
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <memory>
#include <minter/address.h>
#include <minter/public_key.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_data.h>

#ifndef MINTER_TX_TX_SET_HALT_BLOCK_H
#define MINTER_TX_TX_SET_HALT_BLOCK_H

namespace minter {

class MINTER_TX_API tx_set_halt_block : virtual public minter::tx_data {
public:
    tx_set_halt_block(std::shared_ptr<minter::tx> tx);

    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_set_halt_block& set_public_key(const minter::pubkey_t& public_key);
    tx_set_halt_block& set_public_key(const dev::bytes& public_key_bytes);
    tx_set_halt_block& set_height(dev::bigint height);
    tx_set_halt_block& set_height(const std::string& height_num);

    const minter::pubkey_t& get_public_key() const;
    dev::bigint get_height() const;

private:
    minter::pubkey_t m_public_key;
    dev::bigint m_height;
};

} // namespace minter

#endif //MINTER_TX_TX_SET_HALT_BLOCK_H
