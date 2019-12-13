/*!
 * minter_tx.
 * check_tx.h
 *
 * \date 12/10/2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#ifndef MINTER_TX_CHECK_TX_H
#define MINTER_TX_CHECK_TX_H

#include "minter/address.h"
#include "minter/check.h"
#include "minter/minter_tx_config.h"
#include "minter/tx/signature_data.h"
#include "utils.h"

#include <memory>
#include <string>

#define CHECK_ASSERT_NOT_EMPTY(val, name) \
    if (val.empty())                      \
    throw std::runtime_error("can't sign check: " + std::string(#name) + " is empty")

#define CHECK_ASSERT_NOT_ZERO(val, name) \
    if (val == 0)                        \
    throw std::runtime_error("can't sign check: " + std::string(#name) + " is 0")

namespace minter {

class MINTER_TX_API check_tx {
public:
    static dev::bytes_data make_proof(const address_t& address, const dev::bytes& pass);
    static check_tx decode(const std::string& check_data);
    static check_tx decode(const minter::check_t& check);

    check_tx()
        : m_nonce(utils::gen_random_bytes(32)),
          m_chain_id(chain_id::mainnet),
          m_coin("BIP"),
          m_gas_coin(m_coin),
          m_lock(65) {
    }

    check_tx(std::string nonce, std::string pass)
        : m_pass(pass.begin(), pass.end()),
          m_nonce(dev::bytes(nonce.begin(), nonce.end())),
          m_chain_id(chain_id::mainnet),
          m_coin("BIP"),
          m_gas_coin("BIP"),
          m_lock(65) {
    }

    check_tx& set_pass(std::string pass);
    check_tx& set_nonce(std::string nonce);
    check_tx& set_nonce(dev::bytes nonce);
    check_tx& set_chain_id(chain_id net_id);
    check_tx& set_due_block(const dev::bigint& due_block);
    check_tx& set_due_block(const std::string& due_block);
    check_tx& set_due_block(std::string&& due_block);
    check_tx& set_coin(const std::string& coin);
    check_tx& set_gas_coin(const std::string& coin);
    check_tx& set_value(const dev::bigint& raw);
    check_tx& set_value(const dev::bigdec18& normalized);
    check_tx& set_value(const std::string& normalized);

    const dev::bytes& get_pass() const;
    const dev::bytes_data& get_nonce() const;
    chain_id get_chain_id() const;
    const dev::bigint& get_due_block() const;
    const std::string& get_coin() const;
    const std::string& get_gas_coin() const;
    dev::bigdec18 get_value() const;

    minter::check_t sign(const privkey_t& priv_key);

private:
    dev::bytes_data encode(bool sign);

    dev::bytes m_pass;
    dev::bytes_data m_nonce;
    dev::bigint m_chain_id;
    dev::bigint m_due_block;
    std::string m_coin;
    dev::bigint m_value;
    std::string m_gas_coin;
    dev::bytes_data m_lock;
    minter::signature_single_data m_signature;
};

} // namespace minter

#endif //MINTER_TX_CHECK_TX_H
