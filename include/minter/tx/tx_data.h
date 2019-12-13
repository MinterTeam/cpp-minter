/*!
 * minter_tx.
 * tx_data.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_DATA_H
#define MINTER_TX_DATA_H

#include "minter/minter_tx_config.h"

#include <memory>

namespace minter {

// Data for concrete transaction
class MINTER_TX_API tx_data : public std::enable_shared_from_this<minter::tx_data> {
public:
    tx_data() = default;
    explicit tx_data(std::shared_ptr<minter::tx> tx);
    virtual ~tx_data() = default;
    virtual uint16_t type() const = 0;
    virtual dev::bytes encode() = 0;
    virtual void decode(const dev::bytes& data) = 0;
    std::shared_ptr<minter::tx> build();

protected:
    std::shared_ptr<minter::tx> tx();

private:
    std::shared_ptr<minter::tx> m_tx;
};

} // namespace minter

#endif //MINTER_TX_DATA_H
