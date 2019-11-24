/*!
 * minter_tx.
 * transaction.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <cstring>
#include <boost/multiprecision/cpp_int.hpp>
#include <secp256k1/include/secp256k1.h>
#include <secp256k1/include/secp256k1_recovery.h>
#include <secp256k1/include/secp256k1_ecdh.h>
#include <minter/crypto/secp256k1_raii.h>

#include "minter/tx/tx.h"
#include "minter/tx/utils.h"
#include "minter/tx/tx_send_coin.h"
#include "minter/tx/tx_sell_coin.h"
#include "minter/tx/tx_sell_all_coins.h"
#include "minter/tx/tx_buy_coin.h"
#include "minter/tx/tx_create_coin.h"
#include "minter/tx/tx_declare_candidacy.h"
#include "minter/tx/tx_delegate.h"
#include "minter/tx/tx_unbond.h"
#include "minter/tx/tx_redeem_check.h"
#include "minter/tx/tx_set_candidate_on_off.h"
#include "minter/tx/tx_create_multisig_address.h"
#include "minter/tx/tx_multisend.h"
#include "minter/tx/tx_edit_candidate.h"
#include "minter/tx/tx_type.h"

const std::unordered_map<std::string, minter::chain_id> minter::chain_id_str_map = {
    {"mainnet", minter::mainnet},
    {"testnet", minter::testnet},
};

minter::tx::tx() :
    m_chain_id(dev::bigint(chain_id::testnet)),
    m_gas_price(dev::bigint("1")),
    m_gas_coin("MNT"),
    m_payload(dev::bytes(0)),
    m_service_data(dev::bytes(0)) {

}

std::shared_ptr<minter::tx> minter::tx::create() {
    return std::make_shared<minter::tx>();
}

std::shared_ptr<minter::tx> minter::tx::decode(const dev::bytes &tx) {
    dev::RLP s(tx);

    if (s.itemCount() != 10) {
        throw std::runtime_error("Invalid RLP length: required 10 elements");
    }

    auto out = create();

    out->m_nonce = (dev::bigint) s[0];
    out->m_chain_id = (dev::bigint) s[1];
    out->m_gas_price = (dev::bigint) s[2];
    out->m_gas_coin = minter::utils::to_string_clear((dev::bytes) s[3]);
    out->m_type = (dev::bigint) s[4];

    out->m_data = (dev::bytes) s[5];
    out->create_data_from_type();

    out->m_payload = (dev::bytes) s[6];
    out->m_service_data = (dev::bytes) s[7];
    out->m_signature_type = (dev::bigint) s[8];

    if (out->m_signature_type == minter::signature_type::single) {
        out->m_signature = std::make_shared<minter::signature_single_data>();
        const dev::bytes b = (dev::bytes) s[9];
        dev::RLP inn(b);
        dev::RLP sdata = s[9];
        (void)sdata;
        out->m_signature->decode(inn);
    } else if (out->m_signature_type == minter::signature_type::multi) {
        out->m_signature = std::make_shared<minter::signature_multi_data>();
        const dev::bytes b = (dev::bytes) s[9];
        dev::RLP inn(b);
        dev::RLP sdata = s[9];
        (void)sdata;
        out->m_signature->decode(inn);
    }

    return out;
}

std::shared_ptr<minter::tx> minter::tx::decode(const char *hexEncoded) {
    return decode(minter::Data(hexEncoded).get());
}

/// \todo make static map, remove switch-case
void minter::tx::create_data_from_type() {

    // sadly, can't use switch-case on non constexpr type() function, and type can't be constexpr
    if (get_type() == minter::tx_send_coin_type::type()) {
        m_data_raw = minter::tx_send_coin_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_sell_coin_type::type()) {
        m_data_raw = minter::tx_sell_coin_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_sell_all_coins_type::type()) {
        m_data_raw = minter::tx_sell_all_coins_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_buy_coin_type::type()) {
        m_data_raw = minter::tx_buy_coin_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_create_coin_type::type()) {
        m_data_raw = minter::tx_create_coin_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_declare_candidacy_type::type()) {
        m_data_raw = minter::tx_declare_candidacy_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_delegate_type::type()) {
        m_data_raw = minter::tx_delegate_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_unbond_type::type()) {
        m_data_raw = minter::tx_unbond_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_redeem_check_type::type()) {
        m_data_raw = minter::tx_redeem_check_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_set_candidate_on_type::type()) {
        m_data_raw = minter::tx_set_candidate_on_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_set_candidate_off_type::type()) {
        m_data_raw = minter::tx_set_candidate_off_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_create_multisig_address_type::type()) {
        m_data_raw = minter::tx_create_multisig_address_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_multisend_type::type()) {
        m_data_raw = minter::tx_multisend_type::create(shared_from_this(), get_data_raw());
    } else if (get_type() == minter::tx_edit_candidate_type::type()) {
        m_data_raw = minter::tx_edit_candidate_type::create(shared_from_this(), get_data_raw());
    }
}

minter::Data32 minter::tx::get_unsigned_hash(minter::signature_type signType) {
    m_signature_type = signType;
    minter::Data raw_tx_data = minter::Data(encode(true));
    return Data32(minter::utils::sha3k(raw_tx_data));
}

minter::Data minter::tx::sign_external(const minter::signature &sig) {
    if (!sig.success) {
        return minter::Data("0x0");
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return minter::Data(encode(false));
}

minter::Data minter::tx::sign_external(minter::signature &&sign) {
    auto sig = std::move(sign);

    if (!sig.success) {
        return minter::Data("0x0");
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return minter::Data(encode(false));
}

minter::Data minter::tx::sign_external(minter::tx::signer_func_t func) {
    m_signature_type = minter::signature_type::single;

    minter::Data raw_tx_data = minter::Data(encode(true));
    minter::Data32 hash(minter::utils::sha3k(raw_tx_data));

    auto sig = func(std::move(hash));

    if (!sig.success) {
        return minter::Data("0x0");
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return minter::Data(encode(false));
}

minter::Data minter::tx::sign_external(minter::tx::signer_func_c_t func) {
    m_signature_type = minter::signature_type::single;

    minter::Data raw_tx_data = minter::Data(encode(true));
    minter::Data32 hash(minter::utils::sha3k(raw_tx_data));

    auto sig = func(std::move(hash));

    if (!sig.success) {
        return minter::Data("0x0");
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return minter::Data(encode(false));
}

minter::Data minter::tx::sign_single(const minter::data::private_key &pk) {
    m_signature_type = minter::signature_type::single;

    minter::Data raw_tx_data = minter::Data(encode(true));
    minter::Data32 hash(minter::utils::sha3k(raw_tx_data));

    minter::secp256k1_raii secp;
    auto sig = sign_with_private(secp, hash.get(), pk.get());

    if (!sig.success) {
        return minter::Data("0x0");
    }

    std::shared_ptr<minter::signature_single_data> sig_data = std::make_shared<minter::signature_single_data>();
    sig_data->set_signature(sig);
    m_signature = std::move(sig_data);

    return minter::Data(encode(false));
}

minter::Data minter::tx::sign_multiple(const minter::data::address &signatureAddress, const std::vector<minter::data::private_key> &pks) {
    m_signature_type = minter::signature_type::multi;
    if(pks.empty()) {
        //TODO: make ability to on/off exceptions
        return minter::Data("0x0");
    }

    minter::Data raw_tx_data = minter::Data(encode(true));
    minter::Data32 hash(minter::utils::sha3k(raw_tx_data));
    std::vector<minter::signature_single_data> signaturesData;
    signaturesData.reserve(pks.size());

    minter::secp256k1_raii secp;

    for(const auto& pk: pks) {
        auto sig = sign_with_private(secp, hash.get(), pk.get());
        signaturesData.emplace_back(std::move(sig));
    }

    std::shared_ptr<minter::signature_multi_data> multisig = std::make_shared<minter::signature_multi_data>();
    multisig->set_signatures(signatureAddress, std::move(signaturesData));

    m_signature = std::move(multisig);

    return minter::Data(encode(false));
}

minter::signature minter::tx::sign_with_private(const minter::secp256k1_raii &ctx,
                                                const dev::bytes &hash,
                                                const dev::bytes &pk) {
    secp256k1_ecdsa_recoverable_signature sig;

    int ret = secp256k1_ecdsa_sign_recoverable(ctx.get(), &sig, &hash[0], &pk[0], NULL, NULL);

    uint8_t outputSer[65];
    minter::signature outSig;
    int recoveryId = 0;

    if (ret) {
        int serializeRet = secp256k1_ecdsa_recoverable_signature_serialize_compact(
            ctx.get(),
            outputSer,
            &recoveryId,
            &sig);
        (void)serializeRet;
        outputSer[64] = ((uint8_t) recoveryId) + (uint8_t) 27;
    } else {
        return outSig;
    }

    uint8_t r[32], s[32], v[1];
    memcpy(r, outputSer + 0, 32);
    memcpy(s, outputSer + 32, 32);
    v[0] = outputSer[64];
    minter::utils::memset_s(outputSer, 0, 65);

    outSig.r = dev::bytes(r, r + 32);
    outSig.s = dev::bytes(s, s + 32);
    outSig.v = dev::bytes(v, v + 1);
    outSig.success = true;

    return outSig;
}


dev::bytes minter::tx::encode(bool exclude_signature) {
    dev::RLPStream output;
    dev::RLPStream list;
    list.append(m_nonce);
    list.append(m_chain_id);
    list.append(m_gas_price);
    list.append(minter::utils::to_bytes_fixed(m_gas_coin, 10));
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

std::string minter::tx::get_gas_coin() const {
    return m_gas_coin;
}

uint16_t minter::tx::get_type() const {
    return static_cast<uint16_t>(m_type);
}

const dev::bytes &minter::tx::get_data_raw() const {
    return m_data;
}

const dev::bytes &minter::tx::get_payload() const {
    return m_payload;
}

const dev::bytes &minter::tx::get_service_data() const {
    return m_service_data;
}

uint8_t minter::tx::get_signature_type() const {
    return static_cast<uint8_t>(m_signature_type);
}

