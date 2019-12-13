/*!
 * minter_tx.
 * signature_data.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/signature_data.h"

#include "minter/tx/utils.h"

#include <algorithm>
#include <cassert>
#include <iostream>

minter::signature_single_data::signature_single_data(const minter::signature& sig) {
    set_signature(sig);
}

minter::signature_single_data::signature_single_data(minter::signature&& sig) {
    set_signature(std::move(sig));
}

dev::bytes minter::signature_single_data::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;

    if (m_r[0] == 0x0) {
        m_r = dev::bytes_data(m_r).take_range_from(1);
    }
    if (m_s[0] == 0x0) {
        m_s = dev::bytes_data(m_s).take_range_from(1);
    }

    {
        lst.append(m_v);
        lst.append(m_r);
        lst.append(m_s);
        out.appendList(lst);
    }

    return out.out();
}

void minter::signature_single_data::decode(const eth::RLP& data) {
    if (data.itemCount() != 3) {
        throw std::runtime_error("can't decode signature: expected size 3, given: " + utils::to_string(data.itemCount()));
    }
    m_v = (dev::bytes) data[0];
    m_r = (dev::bytes) data[1];
    m_s = (dev::bytes) data[2];
}

void minter::signature_single_data::set_signature(const minter::signature& sig) {
    m_r = sig.r;
    m_s = sig.s;
    m_v = sig.v;
}

void minter::signature_single_data::set_signature(minter::signature&& sig) {
    m_r = std::move(sig.r);
    m_s = std::move(sig.s);
    m_v = std::move(sig.v);
}

void minter::signature_single_data::set_signature(const uint8_t* data) {
    m_r.resize(32);
    m_s.resize(32);
    m_v.resize(1);

    m_r = dev::bytes(data + 00, data + 32);
    m_s = dev::bytes(data + 32, data + 64);
    m_v[0] = data[64];
}

void minter::signature_single_data::set_signature(dev::bytes&& v, dev::bytes&& r, dev::bytes&& s) {
    assert(v.size() == 1);
    assert(r.size() == 32);
    assert(s.size() == 32);
    m_r = std::move(r);
    m_s = std::move(s);
    m_v = std::move(v);
}

void minter::signature_single_data::set_signature(const dev::bytes& v, const dev::bytes& r, const dev::bytes& s) {
    assert(v.size() == 1);
    assert(r.size() == 32);
    assert(s.size() == 32);
    m_r = r;
    m_s = s;
    m_v = v;
}

void minter::signature_single_data::set_signature(dev::bytes&& data) {
    assert(data.size() == 65);
    m_r.resize(32);
    m_s.resize(32);
    m_v.resize(1);

    std::move(data.begin() + 00, data.begin() + 32, m_r.begin());
    std::move(data.begin() + 32, data.begin() + 64, m_s.begin());
    m_v[0] = std::move(data[64]);
}

void minter::signature_single_data::set_signature(const dev::bytes& data) {
    m_r.resize(32);
    m_s.resize(32);
    m_v.resize(1);

    std::copy(data.begin() + 00, data.begin() + 32, m_r.begin());
    std::copy(data.begin() + 32, data.begin() + 64, m_s.begin());
    m_v[0] = std::move(data[64]);
}

const dev::bytes& minter::signature_single_data::get_v() const {
    return m_v;
}

const dev::bytes& minter::signature_single_data::get_r() const {
    return m_r;
}

const dev::bytes& minter::signature_single_data::get_s() const {
    return m_s;
}

std::string minter::signature_single_data::to_hex() const {
    std::stringstream ss;
    ss << dev::bytes_data(get_r()).to_hex();
    ss << dev::bytes_data(get_s()).to_hex();
    ss << dev::bytes_data(get_v()).to_hex();
    return ss.str();
}

bool minter::signature_single_data::empty() const {
    return m_r.empty() || m_s.empty() || m_v.empty();
}

bool minter::signature_single_data::operator==(const class minter::signature_single_data& other) const noexcept {
    return get_r() == other.get_r() && get_s() == other.get_s() && get_v() == other.get_v();
}

minter::signature_multi_data::signature_multi_data(const minter::data::address& address,
                                                   std::vector<minter::signature_single_data>&& signs) {
    set_signatures(address, std::move(signs));
}

dev::bytes minter::signature_multi_data::encode() {
    eth::RLPStream signList;
    for (const auto& item : m_signs) {
        eth::RLPStream signItem;
        signItem.append(item.get_v());
        signItem.append(item.get_r());
        signItem.append(item.get_s());

        signList.appendList(signItem);
    }

    eth::RLPStream out;
    out.append(m_address.get());
    out.appendList(signList);

    return out.out();
}

void minter::signature_multi_data::decode(const eth::RLP& data) {
    eth::RLPStream out;

    m_address = minter::address_t((dev::bytes) data[0]);
    size_t signsLen = data[1].itemCount();
    m_signs.resize(signsLen);

    for (size_t c = 0; c < signsLen; c++) {
        eth::RLP els = data[1][c];
        signature_single_data sd;
        sd.decode(els);
        m_signs[c] = std::move(sd);
    }
}

minter::signature_multi_data& minter::signature_multi_data::set_signatures(const minter::data::address& address,
                                                                           std::vector<minter::signature_single_data>&& signs) {
    m_address = address;
    m_signs = std::move(signs);

    return *this;
}

const minter::address_t& minter::signature_multi_data::get_address() const {
    return m_address;
}

const std::vector<minter::signature_single_data>& minter::signature_multi_data::get_signs() const {
    return m_signs;
}

bool minter::signature_multi_data::operator==(const class minter::signature_multi_data& other) const noexcept {
    if (get_signs().size() != other.get_signs().size()) {
        return false;
    }

    return std::equal(get_signs().begin(), get_signs().end(), other.get_signs().begin());
}
