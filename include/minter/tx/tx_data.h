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

#include <memory>
#include "tx.h"
#include "minter/minter_tx_core.h"

namespace minter {

// Data for concrete transaction
class MINTER_TX_API tx_data: public std::enable_shared_from_this<minter::tx_data> {
public:
    tx_data() = default;
    explicit tx_data(std::shared_ptr<minter::tx> tx) : m_tx(std::move(tx)) { }
    virtual ~tx_data() = default;
    virtual uint16_t type() const = 0;
    virtual dev::bytes encode() = 0;

    void decode(const char* hexEncoded) {
        minter::Data given(hexEncoded);
        decode_internal(dev::RLP(given.get()));
    }
    void decode(const dev::bytes &data) {
        decode_internal(dev::RLP(data));
    }

    std::shared_ptr<minter::tx> build() {
        tx()->m_data = encode();
        tx()->m_data_raw = shared_from_this();
        tx()->m_type = type();

        return tx();
    }

protected:
    virtual void decode_internal(dev::RLP rlp) {};

    std::shared_ptr<minter::tx> tx() {
        return m_tx;
    }
private:
    std::shared_ptr<minter::tx> m_tx;
};


}

#endif //MINTER_TX_DATA_H
