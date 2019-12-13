/*!
 * minter_tx.
 * private_key.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/private_key.h"

#include "minter/crypto/cxx_secp256k1.h"

#include <atomic>
#include <bip3x/HDKeyEncoder.h>
#include <bip3x/utils.h>
#include <cstring>
#include <sstream>

minter::data::private_key minter::data::private_key::from_mnemonic(const std::string& mnem, uint32_t derive_index) {
    return from_mnemonic(mnem.c_str(), derive_index);
}
minter::data::private_key minter::data::private_key::from_mnemonic(const char* mnemonic, uint32_t derive_index) {
    bip3x::bytes_64 seed = bip3x::HDKeyEncoder::makeBip39Seed(std::string(mnemonic));
    bip3x::HDKey hdkey = bip3x::HDKeyEncoder::makeBip32RootKey(seed);

    std::stringstream derivation_path;
    derivation_path << "m/44'/60'/0'/0/";
    derivation_path << derive_index;

    bip3x::HDKeyEncoder::makeExtendedKey(hdkey, derivation_path.str());

    auto out = private_key(std::move(hdkey.privateKey.get()));
    hdkey.clear();
    return out;
}
minter::data::private_key::private_key()
    : bytes_array() {
}
minter::data::private_key::private_key(const char* hexString)
    : bytes_array(std::string(hexString)) {
}
minter::data::private_key::private_key(const std::string& hexString)
    : bytes_array(hexString) {
}

minter::data::private_key::private_key(const uint8_t* data)
    : bytes_array(data) {
}
minter::data::private_key::private_key(std::vector<uint8_t>&& data)
    : bytes_array(data) {
}
minter::data::private_key::private_key(const std::vector<uint8_t>& data)
    : bytes_array(data) {
}
minter::data::private_key::private_key(const uint8_t* data, size_t len)
    : bytes_array(data, len) {
}
minter::pubkey_t minter::data::private_key::get_public_key(bool compressed) const {
    cxx_secp256k1 secp;
    secp256k1_pubkey pubkey;

    auto ret = secp256k1_ec_pubkey_create(secp.get(), &pubkey, cdata());

    uint8_t output_ser[65];
    memset(output_ser, 0, 65);
    size_t output_len = 65;

    uint32_t compFlag = compressed == ((uint8_t) 1) ? SECP256K1_EC_COMPRESSED : SECP256K1_EC_UNCOMPRESSED; // NOLINT(hicpp-signed-bitwise)

    if (ret) {
        int ret2 = secp256k1_ec_pubkey_serialize(secp.get(), output_ser, &output_len, &pubkey, compFlag);
        (void) ret2;
    }

    dev::bytes tmp(output_ser, output_ser + output_len);
    minter::pubkey_t out(tmp);

    return out;
}

bool minter::data::private_key::operator==(const minter::data::private_key& other) const noexcept {
    return m_data == other.m_data;
}
bool minter::data::private_key::operator!=(const minter::data::private_key& other) const noexcept {
    return !(operator==(other));
}

std::string minter::data::private_key::to_string() const {
    return to_hex();
}
minter::data::private_key::operator std::string() const {
    return to_string();
}

std::ostream& operator<<(std::ostream& os, const minter::privkey_t& privkey) {
    os << privkey.to_string();
    return os;
}
