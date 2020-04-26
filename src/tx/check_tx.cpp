/*!
 * minter_tx.
 * check_tx.cpp
 *
 * \date 12/10/2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/check_tx.h"

#include "minter/crypto/cxx_secp256k1.h"
#include "minter/tx/utils.h"

#include <exception>
#include <stdexcept>

dev::bytes_data minter::check_tx::make_proof(const minter::address_t& address, const dev::bytes& pass) {
    dev::bytes_data key(pass);
    key.switch_map([](dev::bytes source) {
        return utils::sha256(source);
    });

    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst << address.get();
        out.appendList(lst);
    }

    dev::bytes_data encoded_address(out.out());
    encoded_address.switch_map([](dev::bytes source) {
        return utils::sha3k(source);
    });

    cxx_secp256k1 secp;
    auto signature = secp.sign_message(encoded_address, key);
    if (!signature.success) {
        throw std::runtime_error("can't make a proof");
    }

    signature.v[0] = signature.v[0] == 27 ? 0x0 : (uint8_t) 0x01;

    dev::bytes_data proof;
    proof.write_back(signature.r);
    proof.write_back(signature.s);
    proof.write_back(signature.v);

    return proof;
}

minter::check_tx& minter::check_tx::set_pass(std::string pass) {
    m_pass = dev::bytes(pass.begin(), pass.end());
    return *this;
}

minter::check_tx& minter::check_tx::set_nonce(std::string nonce) {
    m_nonce = dev::bytes_data::from_string_raw(nonce);
    return *this;
}

minter::check_tx& minter::check_tx::set_nonce(dev::bytes nonce) {
    m_nonce = std::move(nonce);
    return *this;
}

minter::check_tx& minter::check_tx::set_chain_id(enum minter::chain_id net_id) {
    m_chain_id = net_id;
    return *this;
}

minter::check_tx& minter::check_tx::set_due_block(const dev::bigint& due_block) {
    m_due_block = due_block;
    return *this;
}

minter::check_tx& minter::check_tx::set_due_block(const std::string& due_block) {
    m_due_block = dev::bigint(due_block);
    return *this;
}

minter::check_tx& minter::check_tx::set_due_block(std::string&& due_block) {
    m_due_block = dev::bigint(std::move(due_block));
    return *this;
}

minter::check_tx& minter::check_tx::set_coin(const std::string& coin) {
    m_coin = coin;
    return *this;
}

minter::check_tx& minter::check_tx::set_gas_coin(const std::string& coin) {
    m_gas_coin = coin;
    return *this;
}

minter::check_tx& minter::check_tx::set_value(const dev::bigint& raw) {
    m_value = raw;
    return *this;
}

minter::check_tx& minter::check_tx::set_value(const dev::bigdec18& normalized) {
    m_value = minter::utils::normalize_value(normalized);
    return *this;
}

minter::check_tx& minter::check_tx::set_value(const std::string& normalized) {
    m_value = minter::utils::normalize_value(normalized);
    return *this;
}

const dev::bytes& minter::check_tx::get_pass() const {
    return m_pass;
}
const dev::bytes_data& minter::check_tx::get_nonce() const {
    return m_nonce;
}
minter::chain_id minter::check_tx::get_chain_id() const {
    return (minter::chain_id)((int) m_chain_id);
}
const dev::bigint& minter::check_tx::get_due_block() const {
    return m_due_block;
}
const std::string& minter::check_tx::get_coin() const {
    return m_coin;
}
const std::string& minter::check_tx::get_gas_coin() const {
    return m_gas_coin;
}
dev::bigdec18 minter::check_tx::get_value() const {
    return minter::utils::humanize_value(m_value);
}

minter::check_tx minter::check_tx::decode(const std::string& check) {
    return decode(minter::check_t(check));
}

minter::check_tx minter::check_tx::decode(const minter::check_t& check) {
    eth::RLP rlp(check.get());
    if (rlp.itemCount() != 10) {
        throw std::runtime_error("invalid check data size: expected 10, given: " + utils::to_string(rlp.itemCount()));
    }

    minter::check_tx tx;
    size_t i = 0;
    tx.m_nonce = (dev::bytes_data) rlp[i++];
    tx.m_chain_id = (dev::bigint) rlp[i++];
    tx.m_due_block = (dev::bigint) rlp[i++];
    tx.m_coin = minter::utils::to_string_clear((dev::bytes) rlp[i++]);
    tx.m_value = (dev::bigint) rlp[i++];
    tx.m_gas_coin = minter::utils::to_string_clear((dev::bytes) rlp[i++]);
    tx.m_lock = (dev::bytes_data) rlp[i++];

    dev::bytes v = (dev::bytes) rlp[i++];
    dev::bytes r = (dev::bytes) rlp[i++];
    dev::bytes s = (dev::bytes) rlp[i++];
    tx.m_signature.set_signature(std::move(v), std::move(r), std::move(s));

    return tx;
}

dev::bytes_data minter::check_tx::encode(bool sign) {
    eth::RLPStream out;
    eth::RLPStream lst;

    lst << m_nonce;
    lst << m_chain_id;
    lst << m_due_block;
    lst << minter::utils::to_bytes_fixed(m_coin, 10);
    lst << m_value;
    lst << minter::utils::to_bytes_fixed(m_gas_coin, 10);

    if (sign) {
        out.appendList(lst);
        return out.out();
    }

    if (!m_signature.empty()) {
        lst << m_lock;
        lst << m_signature.get_v();
        lst << m_signature.get_r();
        lst << m_signature.get_s();
        out.appendList(lst);

        return out.out();
    }

    lst << m_lock;
    out.appendList(lst);

    return out.out();
}

minter::check_t minter::check_tx::sign(const minter::privkey_t& priv_key) {
    CHECK_ASSERT_NOT_EMPTY(m_pass, "passphrase");
    CHECK_ASSERT_NOT_ZERO(m_chain_id, "chain id");
    CHECK_ASSERT_NOT_ZERO(m_due_block, "due block");
    CHECK_ASSERT_NOT_EMPTY(m_nonce, "nonce data");
    CHECK_ASSERT_NOT_EMPTY(m_coin, "coin");
    CHECK_ASSERT_NOT_EMPTY(m_gas_coin, "gas coin");

    toolbox::data::bytes_data hash = encode(true);
    hash.switch_map(utils::to_sha3k);

    dev::bytes_data pk(m_pass);
    pk.switch_map(utils::to_sha256);

    cxx_secp256k1 secp;

    auto lock_sign = secp.sign_message(hash.get(), pk.get());
    if (!lock_sign.success) {
        throw std::runtime_error("unable to create check lock");
    }

    lock_sign.v[0] = lock_sign.v[0] == 27 ? 0x0 : (uint8_t) 0x01;

    m_lock.write(0, lock_sign.r);
    m_lock.write(32, lock_sign.s);
    m_lock.write(64, lock_sign.v);

    dev::bytes_data with_lock = encode(false);
    with_lock.switch_map(utils::to_sha3k);

    signature sign = secp.sign_message(with_lock.get(), priv_key.get());
    if (!lock_sign.success) {
        throw std::runtime_error("unable to sign check");
    }
    m_signature.set_signature(std::move(sign));

    return minter::check_t(encode(false));
}
