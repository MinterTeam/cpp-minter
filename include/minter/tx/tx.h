/*!
 * minter_tx.
 * transaction.hpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_H
#define MINTER_TX_H

#include <memory>
#include <unordered_map>
#include <secp256k1.h>
#include <secp256k1_ecdh.h>
#include <secp256k1_recovery.h>
#include <minter/bip39/utils.h>
#include <boost/multiprecision/cpp_int.hpp>
#include "minter/eth/RLP.h"
#include "minter/eth/vector_ref.h"
#include "minter/address.h"
#include "minter/private_key.h"
#include "signature_data.h"
#include "signature.h"
#include "tx_fwd.h"
#include "minter/crypto/secp256k1_raii.h"
#include "minter/minter_tx_core.h"

namespace minter {

typedef enum {
  mainnet = (uint8_t) 0x01,
  testnet = (uint8_t) 0x02,
} chain_id;

MINTER_TX_API extern const std::unordered_map<std::string, chain_id> chain_id_str_map;

class MINTER_TX_API tx_builder;

class MINTER_TX_API tx : public std::enable_shared_from_this<minter::tx> {
    friend class tx_builder;
    friend class tx_data;
public:
    using signer_func_t = std::function<minter::signature(minter::Data32)>;
    typedef minter::signature (*signer_func_c_t)(minter::Data32);

    static std::shared_ptr<minter::tx> create();
    static std::shared_ptr<minter::tx> decode(const char *encodedHex);
    static std::shared_ptr<minter::tx> decode(const dev::bytes &tx);
    /// \brief DON'T use it directly, otherwise bad_weak_ptr exception will threw
    tx();
    virtual ~tx() = default;

    dev::bigint get_nonce() const;
    uint8_t get_chain_id() const;
    dev::bigint get_gas_price() const;
    std::string get_gas_coin() const;
    uint16_t get_type() const;
    template<typename T = minter::tx_data>
    std::shared_ptr<T> get_data() const {
        return std::dynamic_pointer_cast<T>(m_data_raw);
    }
    const dev::bytes &get_data_raw() const;
    const dev::bytes &get_payload() const;
    const dev::bytes &get_service_data() const;
    uint8_t get_signature_type() const;
    template<typename T>
    std::shared_ptr<T> get_signature_data() const {
        return std::dynamic_pointer_cast<T>(m_signature);
    }

    /// \brief Returns keccak transaction hash, that must be signed with secp256k1 private key
    /// \param signType single or multiple signatures required (default - single sig)
    /// \return 32 bytes keccak hash
    minter::Data32 get_unsigned_hash(minter::signature_type signType = minter::signature_type::single);

    /// \brief Make transaction from external signature
    /// \param sign external signature
    /// \return rlp encoded transaction data with signature info
    minter::Data sign_external(const minter::signature &sign);

    /// \brief Make transaction from external signature
    /// \param sign external signature
    /// \return rlp encoded transaction data with signature info
    minter::Data sign_external(minter::signature &&sign);

    /// \brief Sign transaction with function callback
    /// \see minter::tx::signer_func_c_t - it's a C-style callback, you can assign it to static function
    /// \param func C-style callback function. Signature of callback: minter::signature(minter::Data32 hash)
    /// \return rlp encoded transaction data with signature info
    minter::Data sign_external(signer_func_c_t func);

    /// \brief Sign transaction with function callback
    /// \see minter::tx::signer_func_c_t - it's a C++-style std::function callback
    /// \param func C++ - style callback std::function. Signature of callback: minter::signature(minter::Data32 hash)
    /// \return rlp encoded transaction data with signature info
    minter::Data sign_external(signer_func_t func);

    /// \brief Sign transaction with passed private key
    /// \param pk private key data
    /// \return rlp encoded transaction data with signature info
    minter::Data sign_single(const minter::data::private_key &pk);

    /// \brief Sign multisig transaction with passed private keys and owner signatureAddress
    /// \param signatureAddress owner address
    /// \param pks list of private keys
    /// \return rlp encoded transaction data with multisig signature info
    minter::Data sign_multiple(const minter::data::address &signatureAddress, const std::vector<minter::data::private_key> &pks);

protected:
    dev::bytes encode(bool exclude_signature);
    minter::signature sign_with_private(const minter::secp256k1_raii &ctx,
                                        const dev::bytes &hash,
                                        const dev::bytes &pk);
    void create_data_from_type();

private:
    dev::bigint m_nonce;
    dev::bigint m_chain_id;
    dev::bigint m_gas_price;
    std::string m_gas_coin;
    dev::bigint m_type;
    dev::bytes m_data;
    std::shared_ptr<minter::tx_data> m_data_raw;
    dev::bytes m_payload;
    dev::bytes m_service_data;
    dev::bigint m_signature_type;
    std::shared_ptr<minter::signature_data> m_signature;
};

}

#endif //MINTER_TX_H
