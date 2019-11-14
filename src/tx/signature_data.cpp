/*!
 * minter_tx.
 * signature_data.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include "minter/tx/signature_data.h"
#include "minter/tx/utils.h"

minter::signature_single_data::signature_single_data(const minter::signature &sig) {
    set_signature(sig);
}

minter::signature_single_data::signature_single_data(minter::signature &&sig) {
    set_signature(std::move(sig));
}

dev::bytes minter::signature_single_data::encode() {
    dev::RLPStream out;
    dev::RLPStream lst;
    {
        lst.append(m_v);
        lst.append(m_r);
        lst.append(m_s);
        out.appendList(lst);
    }

    return out.out();
}

void minter::signature_single_data::decode(const dev::RLP &data) {
    m_v = (dev::bytes) data[0];
    m_r = (dev::bytes) data[1];
    m_s = (dev::bytes) data[2];
}

void minter::signature_single_data::set_signature(const minter::signature &sig) {
    m_r = sig.r;
    m_s = sig.s;
    m_v = sig.v;
}

void minter::signature_single_data::set_signature(minter::signature &&sig) {
    auto tmp = std::move(sig);

    m_r = std::move(sig.r);
    m_s = std::move(sig.s);
    m_v = std::move(sig.v);
}

void minter::signature_single_data::set_signature(const uint8_t *data) {
    m_r.resize(32);
    m_s.resize(32);
    m_v.resize(1);

    m_r = dev::bytes(data + 00, data + 32);
    m_s = dev::bytes(data + 32, data + 64);
    m_v[0] = data[64];

}

void minter::signature_single_data::set_signature(dev::bytes &&v, dev::bytes &&r, dev::bytes &&s) {
    assert(v.size() == 1);
    assert(r.size() == 32);
    assert(s.size() == 32);
    m_r = std::move(r);
    m_s = std::move(s);
    m_v = std::move(v);
}

void minter::signature_single_data::set_signature(const dev::bytes &v, const dev::bytes &r, const dev::bytes &s) {
    assert(v.size() == 1);
    assert(r.size() == 32);
    assert(s.size() == 32);
    m_r = r;
    m_s = s;
    m_v = v;
}

void minter::signature_single_data::set_signature(dev::bytes &&data) {
    assert(data.size() == 65);
    m_r.resize(32);
    m_s.resize(32);
    m_v.resize(1);

    std::move(data.begin() + 00, data.begin() + 32, m_r.begin());
    std::move(data.begin() + 32, data.begin() + 64, m_s.begin());
    m_v[0] = std::move(data[64]);
}

void minter::signature_single_data::set_signature(const dev::bytes &data) {
    m_r.resize(32);
    m_s.resize(32);
    m_v.resize(1);

    std::copy(data.begin() + 00, data.begin() + 32, m_r.begin());
    std::copy(data.begin() + 32, data.begin() + 64, m_s.begin());
    m_v[0] = std::move(data[64]);
}

const dev::bytes &minter::signature_single_data::get_v() const {
    return m_v;
}

const dev::bytes &minter::signature_single_data::get_r() const {
    return m_r;
}

const dev::bytes &minter::signature_single_data::get_s() const {
    return m_s;
}

minter::signature_multi_data::signature_multi_data(const minter::data::address &address,
                                                   std::vector<minter::signature_single_data> &&signs) {
    set_signatures(address, std::move(signs));
}

dev::bytes minter::signature_multi_data::encode() {
    dev::RLPStream signList;
    for (const auto &item: m_signs) {
        dev::RLPStream signItem;
        signItem.append(item.get_v());
        signItem.append(item.get_r());
        signItem.append(item.get_s());

        signList.appendList(signItem);
    }

    dev::RLPStream out;
    out.append(m_address.get());
    out.appendList(signList);

    return out.out();
}

void minter::signature_multi_data::decode(const dev::RLP &data) {
    dev::RLPStream out;

    m_address = minter::address_t((dev::bytes) data[0]);
    size_t signsLen = data[1].itemCount();
    m_signs.resize(signsLen);

    for (size_t c = 0; c < signsLen; c++) {
        dev::RLP els = data[1][c];
        signature_single_data sd;
        sd.decode(els);
        m_signs[c] = std::move(sd);
    }
}

minter::signature_multi_data &minter::signature_multi_data::set_signatures(const minter::data::address &address,
                                                                           std::vector<minter::signature_single_data> &&signs) {
    m_address = address;
    m_signs = std::move(signs);

    return *this;
}

const minter::address_t &minter::signature_multi_data::get_address() const {
    return m_address;
}

const std::vector<minter::signature_single_data> &minter::signature_multi_data::get_signs() const {
    return m_signs;
}


