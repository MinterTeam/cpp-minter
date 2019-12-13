/*!
 * minter_tx.
 * signature_data.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_SIGNATURE_DATA_H
#define MINTER_SIGNATURE_DATA_H

#include "minter/address.h"
#include "minter/eth/RLP.h"
#include "minter/minter_tx_config.h"
#include "minter/tx/signature.h"

#include <memory>
#include <vector>

namespace minter {

class MINTER_TX_API signature_data {
public:
    virtual dev::bytes encode() = 0;
    virtual void decode(const eth::RLP& data) = 0;
    virtual ~signature_data() = default;
};

using signature_data_ptr = std::shared_ptr<signature_data>;

class MINTER_TX_API signature_single_data : public virtual minter::signature_data {
public:
    signature_single_data() = default;
    explicit signature_single_data(const minter::signature& sig);
    explicit signature_single_data(minter::signature&& sig);

    void set_signature(const minter::signature& sig);
    void set_signature(minter::signature&& sig);
    void set_signature(const uint8_t* data);
    void set_signature(dev::bytes&& v, dev::bytes&& r, dev::bytes&& s);
    void set_signature(const dev::bytes& v, const dev::bytes& r, const dev::bytes& s);
    void set_signature(dev::bytes&& data);
    void set_signature(const dev::bytes& data);
    const dev::bytes& get_v() const;
    const dev::bytes& get_r() const;
    const dev::bytes& get_s() const;

    std::string to_hex() const;

    bool operator==(const signature_single_data& other) const noexcept;
    bool empty() const;

    dev::bytes encode() override;
    void decode(const eth::RLP& data) override;

private:
    dev::bytes m_v, m_r, m_s;
};

class MINTER_TX_API signature_multi_data : public virtual minter::signature_data {
public:
    signature_multi_data() = default;
    signature_multi_data(const minter::data::address& address, std::vector<minter::signature_single_data>&& signs);
    signature_multi_data& set_signatures(const minter::data::address& address, std::vector<minter::signature_single_data>&& signs);
    dev::bytes encode() override;
    void decode(const eth::RLP& data) override;

    const minter::address_t& get_address() const;
    const std::vector<minter::signature_single_data>& get_signs() const;

    bool operator==(const signature_multi_data& other) const noexcept;

private:
    minter::data::address m_address;
    std::vector<minter::signature_single_data> m_signs;
};

} // namespace minter

#endif //MINTER_SIGNATURE_DATA_H
