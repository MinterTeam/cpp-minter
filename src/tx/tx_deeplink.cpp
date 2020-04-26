/*!
 * minter_tx.
 * tx_deeplink.cpp
 *
 * \date 03/12/2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <minter/eth/RLP.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_data.h>
#include <minter/tx/tx_deeplink.h>
#include <minter/tx/utils.h>

std::shared_ptr<minter::tx_deeplink> minter::tx_deeplink::decode(const std::string& encoded_hex) {
    dev::bytes_data d(encoded_hex);
    return decode(d.get());
}
std::shared_ptr<minter::tx_deeplink> minter::tx_deeplink::decode(const dev::bytes_data& tx) {
    return decode(tx.get());
}

std::shared_ptr<minter::tx_deeplink> minter::tx_deeplink::decode(const dev::bytes& tx) {
    eth::RLP s(tx);
    std::shared_ptr<minter::tx_deeplink> out = std::make_shared<minter::tx_deeplink>(minter::tx::create());

    out->m_tx->m_type = (dev::bigint) s[0];
    out->m_tx->m_data = (dev::bytes) s[1];
    out->m_tx->create_data_from_type();
    out->m_tx->m_payload = (dev::bytes) s[2];
    out->m_tx->m_nonce = (dev::bigint) s[3];
    out->m_tx->m_gas_price = (dev::bigint) s[4];
    out->m_tx->m_gas_coin = minter::utils::to_string_clear((dev::bytes) s[5]);

    return out;
}

minter::tx_deeplink::tx_deeplink(std::shared_ptr<minter::tx>&& tx)
    : m_tx(tx) {
}

dev::bytes_data minter::tx_deeplink::encode() const {
    eth::RLPStream output;
    eth::RLPStream list;
    list.append(m_tx->get_type());
    list.append(m_tx->get_data_raw());
    list.append(m_tx->get_payload());
    list.append(m_tx->get_nonce());
    list.append(m_tx->get_gas_price());
    list.append(minter::utils::to_bytes_fixed(m_tx->get_gas_coin(), 10));

    output.appendList(list);
    return dev::bytes_data(output.out());
}

const std::shared_ptr<minter::tx>& minter::tx_deeplink::get_tx() const {
    return m_tx;
}

std::string minter::tx_deeplink::to_url(const std::string& base_domain, const std::string& check_pass) const {
    std::stringstream ss;
    ss << base_domain;
    if (base_domain[base_domain.size() - 1] != '/') {
        ss << "/";
    }
    ss << "tx/";
    dev::bytes_data deeplinkRaw = encode();
    deeplinkRaw.switch_map(minter::utils::to_base64_web);
    ss << deeplinkRaw.to_string();

    if (!check_pass.empty()) {
        ss << "?p=";
        dev::bytes_data check_raw = dev::bytes_data::from_string_raw(check_pass);
        check_raw.switch_map(minter::utils::to_base64_web);
        ss << check_raw.to_string();
    }

    return ss.str();
}
