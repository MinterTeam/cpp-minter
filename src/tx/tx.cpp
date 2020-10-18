/*!
 * minter_tx.
 * transaction.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx.h"

#include "minter/tx/tx_buy_coin.h"
#include "minter/tx/tx_create_coin.h"
#include "minter/tx/tx_create_multisig_address.h"
#include "minter/tx/tx_declare_candidacy.h"
#include "minter/tx/tx_delegate.h"
#include "minter/tx/tx_edit_candidate.h"
#include "minter/tx/tx_edit_candidate_public_key.h"
#include "minter/tx/tx_edit_coin_owner.h"
#include "minter/tx/tx_edit_multisig.h"
#include "minter/tx/tx_multisend.h"
#include "minter/tx/tx_price_vote.h"
#include "minter/tx/tx_recreate_coin.h"
#include "minter/tx/tx_redeem_check.h"
#include "minter/tx/tx_sell_all_coins.h"
#include "minter/tx/tx_sell_coin.h"
#include "minter/tx/tx_send_coin.h"
#include "minter/tx/tx_set_candidate_on_off.h"
#include "minter/tx/tx_set_halt_block.h"
#include "minter/tx/tx_type.h"
#include "minter/tx/tx_unbond.h"
#include "minter/tx/utils.h"

#include <cstring>
#include <minter/crypto/cxx_secp256k1.h>
#include <unordered_map>

using namespace minter;

const std::unordered_map<std::string, minter::chain_id> minter::chain_id_str_map = {
    {"mainnet", minter::mainnet},
    {"testnet", minter::testnet},
};

const dev::bigint minter::def_coin_id = dev::bigint(0);

minter::tx::tx()
    : m_chain_id(dev::bigint(chain_id::mainnet)),
      m_gas_price(dev::bigint("1")),
      m_gas_coin_id(dev::bigint(0)),
      m_payload(dev::bytes(0)),
      m_service_data(dev::bytes(0)) {
}

std::shared_ptr<minter::tx> minter::tx::create() {
    return std::make_shared<minter::tx>();
}

std::shared_ptr<minter::tx> minter::tx::decode(const char* hexEncoded) {
    dev::bytes_data d(hexEncoded);
    return decode(d.get());
}

std::shared_ptr<minter::tx> minter::tx::decode(const dev::bytes_data& tx) {
    return decode(tx.get());
}

std::shared_ptr<minter::tx> minter::tx::decode(const dev::bytes& tx) {
    eth::RLP s(tx);

    if (s.itemCount() != 10) {
        throw std::runtime_error("Invalid RLP length: required 10 elements");
    }

    auto out = create();

    out->m_nonce = (dev::bigint) s[0];
    out->m_chain_id = (dev::bigint) s[1];
    out->m_gas_price = (dev::bigint) s[2];
    out->m_gas_coin_id = (dev::bigint) s[3];
    out->m_type = (dev::bigint) s[4];

    out->m_data = (dev::bytes) s[5];
    out->create_data_from_type();

    out->m_payload = (dev::bytes) s[6];
    out->m_service_data = (dev::bytes) s[7];
    out->m_signature_type = (dev::bigint) s[8];

    if (out->m_signature_type == minter::signature_type::single) {
        out->m_signature = std::make_shared<minter::signature_single_data>();
        const dev::bytes b = (dev::bytes) s[9];
        eth::RLP inn(b);
        eth::RLP sdata = s[9];
        (void) sdata;
        out->m_signature->decode(inn);
    } else if (out->m_signature_type == minter::signature_type::multi) {
        out->m_signature = std::make_shared<minter::signature_multi_data>();
        const dev::bytes b = (dev::bytes) s[9];
        eth::RLP inn(b);
        eth::RLP sdata = s[9];
        (void) sdata;
        out->m_signature->decode(inn);
    }

    return out;
}

/// \todo make static map, remove switch-case
void minter::tx::create_data_from_type() {
    switch (get_type()) {
    case tx_send_coin_type.type():
        m_data_raw = tx_send_coin_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_sell_coin_type.type():
        m_data_raw = tx_sell_coin_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_sell_all_coins_type.type():
        m_data_raw = tx_sell_all_coins_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_buy_coin_type.type():
        m_data_raw = tx_buy_coin_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_create_coin_type.type():
        m_data_raw = tx_create_coin_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_declare_candidacy_type.type():
        m_data_raw = tx_declare_candidacy_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_delegate_type.type():
        m_data_raw = tx_delegate_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_unbond_type.type():
        m_data_raw = tx_unbond_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_redeem_check_type.type():
        m_data_raw = tx_redeem_check_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_set_candidate_on_type.type():
        m_data_raw = tx_set_candidate_on_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_set_candidate_off_type.type():
        m_data_raw = tx_set_candidate_off_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_create_multisig_address_type.type():
        m_data_raw = tx_create_multisig_address_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_multisend_type.type():
        m_data_raw = tx_multisend_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_edit_candidate_type.type():
        m_data_raw = tx_edit_candidate_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_set_halt_block_type.type():
        m_data_raw = tx_set_halt_block_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_recreate_coin_type.type():
        m_data_raw = tx_recreate_coin_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_edit_coin_owner_type.type():
        m_data_raw = tx_edit_coin_owner_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_edit_multisig_type.type():
        m_data_raw = tx_edit_multisig_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_edit_candidate_public_key_type.type():
        m_data_raw = tx_edit_candidate_public_key_type.create(shared_from_this(), get_data_raw());
        break;
    case tx_price_vote_type.type():
        m_data_raw = tx_price_vote_type.create(shared_from_this(), get_data_raw());
        break;
    default:
        throw std::runtime_error("Unknown tx type: " + minter::utils::to_string(m_type));
    }
}

dev::bytes_32 minter::tx::get_unsigned_hash(minter::signature_type signType) {
    m_signature_type = signType;
    dev::bytes_data raw_tx_data = dev::bytes_data(encode(true));
    return dev::bytes_32(minter::utils::sha3k(raw_tx_data));
}

dev::bytes_data minter::tx::sign_single_external(const minter::signature& sign) {
    if (!sign.success) {
        return dev::bytes_data();
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sign);
    m_signature = std::move(sig_data);

    return dev::bytes_data(encode(false));
}

dev::bytes_data minter::tx::sign_single_external(minter::signature&& sign) {
    auto sig = std::move(sign);

    if (!sig.success) {
        return dev::bytes_data();
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return dev::bytes_data(encode(false));
}

dev::bytes_data minter::tx::sign_single_external(minter::tx::signer_func_t func) {
    m_signature_type = minter::signature_type::single;

    dev::bytes_data raw_tx_data = dev::bytes_data(encode(true));
    dev::bytes_32 hash(minter::utils::sha3k(raw_tx_data));

    auto sig = func(std::move(hash));

    if (!sig.success) {
        return dev::bytes_data();
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return dev::bytes_data(encode(false));
}

dev::bytes_data minter::tx::sign_single_external(minter::tx::signer_func_c_t func) {
    m_signature_type = minter::signature_type::single;

    dev::bytes_data raw_tx_data = dev::bytes_data(encode(true));
    dev::bytes_32 hash(minter::utils::sha3k(raw_tx_data));

    auto sig = func(std::move(hash));

    if (!sig.success) {
        return dev::bytes_data();
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return dev::bytes_data(encode(false));
}

dev::bytes_data minter::tx::sign_single(const minter::data::private_key& pk) {
    m_signature_type = minter::signature_type::single;

    dev::bytes_data raw_tx_data = dev::bytes_data(encode(true));
    dev::bytes_32 hash(minter::utils::sha3k(raw_tx_data));

    minter::cxx_secp256k1 secp;
    auto sig = secp.sign_message(hash, pk);

    if (!sig.success) {
        return dev::bytes_data();
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return dev::bytes_data(encode(false));
}

minter::signature minter::tx::sign_only_single(const minter::privkey_t& pk) {
    m_signature_type = minter::signature_type::single;

    dev::bytes_data raw_tx_data = dev::bytes_data(encode(true));
    dev::bytes_32 hash(minter::utils::sha3k(raw_tx_data));

    minter::cxx_secp256k1 secp;
    return secp.sign_message(hash, pk);
}

dev::bytes_data minter::tx::sign_multiple(const minter::data::address& signatureAddress, const std::vector<minter::privkey_t>& pks) {
    m_signature_type = minter::signature_type::multi;
    if (pks.empty()) {
        throw std::runtime_error("empty private key passed");
    }

    dev::bytes_data raw_tx_data = dev::bytes_data(encode(true));
    dev::bytes_32 hash(minter::utils::sha3k(raw_tx_data));
    std::vector<minter::signature_single_data> signaturesData;
    signaturesData.reserve(pks.size());

    minter::cxx_secp256k1 secp;

    for (const auto& pk : pks) {
        auto sig = secp.sign_message(hash.get(), pk.get());
        signaturesData.emplace_back(std::move(sig));
    }

    std::shared_ptr<minter::signature_multi_data> multisig = std::make_shared<minter::signature_multi_data>();
    multisig->set_signatures(signatureAddress, std::move(signaturesData));

    m_signature = std::move(multisig);

    return dev::bytes_data(encode(false));
}

minter::signature minter::tx::sign_only_multiple(const minter::privkey_t& pk) {
    m_signature_type = minter::signature_type::multi;

    dev::bytes_data raw_tx_data = dev::bytes_data(encode(true));
    dev::bytes_32 hash(minter::utils::sha3k(raw_tx_data));

    minter::cxx_secp256k1 secp;
    return secp.sign_message(hash, pk);
}

dev::bytes_data minter::tx::sign_multiple_external(const minter::address_t& signatureAddress, const std::vector<minter::signature>&& signatures) {
    m_signature_type = minter::signature_type::multi;
    if (signatures.empty()) {
        throw std::runtime_error("signatures list is empty");
    }

    std::vector<minter::signature_single_data> signaturesData(signatures.size());

    for (size_t i = 0; i < signatures.size(); i++) {
        signaturesData[i] = minter::signature_single_data(std::move(signatures[i]));
    }

    std::shared_ptr<minter::signature_multi_data> multisig = std::make_shared<minter::signature_multi_data>();
    multisig->set_signatures(signatureAddress, std::move(signaturesData));

    m_signature = std::move(multisig);

    return dev::bytes_data(encode(false));
}

dev::bytes minter::tx::encode(bool exclude_signature) {
    eth::RLPStream output;
    eth::RLPStream list;
    list.append(m_nonce);
    list.append(m_chain_id);
    list.append(m_gas_price);
    list.append(m_gas_coin_id);
    list.append(m_type);
    list.append(m_data);
    list.append(m_payload);
    list.append(m_service_data);
    list.append(m_signature_type);

    if (exclude_signature) {
        output.appendList(list);
        return output.out();
    }

    list.append(m_signature->encode());
    output.appendList(list);
    return output.out();
}

// GETTERS
dev::bigint minter::tx::get_nonce() const {
    return m_nonce;
}

uint8_t minter::tx::get_chain_id() const {
    return static_cast<uint8_t>(m_chain_id);
}

dev::bigint minter::tx::get_gas_price() const {
    return m_gas_price;
}

dev::bigint minter::tx::get_gas_coin_id() const {
    return m_gas_coin_id;
}

uint8_t minter::tx::get_type() const {
    return static_cast<uint8_t>(m_type);
}

const dev::bytes& minter::tx::get_data_raw() const {
    return m_data;
}

const dev::bytes& minter::tx::get_payload() const {
    return m_payload;
}

const dev::bytes& minter::tx::get_service_data() const {
    return m_service_data;
}

uint8_t minter::tx::get_signature_type() const {
    return static_cast<uint8_t>(m_signature_type);
}
