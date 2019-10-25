/*!
 * minter_tx.
 * private_key.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <sstream>
#include "minter/private_key.h"
minter::data::private_key minter::data::private_key::from_mnemonic(const std::string &mnem, uint32_t derive_index) {
    return from_mnemonic(mnem.c_str(), derive_index);
}
minter::data::private_key minter::data::private_key::from_mnemonic(const char *mnemonic,
                                                                                 uint32_t derive_index) {
    private_key out;

    minter::Data64 seed = minter::HDKeyEncoder::makeBip39Seed(std::string(mnemonic));
    minter::HDKey root_key = minter::HDKeyEncoder::makeBip32RootKey(seed);

    std::stringstream derivation_path;
    derivation_path << "m/44'/60'/0'/0/";
    derivation_path << derive_index;

    minter::HDKey ext_key = minter::HDKeyEncoder::makeExtendedKey(root_key, derivation_path.str());

    std::copy(ext_key.privateKey.get().begin(), ext_key.privateKey.get().end(), out.get().begin());

    return out;
}
minter::data::private_key::private_key() : FixedData() {
}
minter::data::private_key::private_key(const char *hexString) : FixedData() {
    m_data = std::move(minter::hexToBytes(hexString));
}
minter::data::private_key::private_key(const uint8_t *data) : FixedData(data) {

}
minter::data::private_key::private_key(std::vector<uint8_t> &&data) : FixedData(data) {

}
minter::data::private_key::private_key(const std::vector<uint8_t> &data) : FixedData(data) {

}
minter::data::private_key::private_key(const uint8_t *data, size_t len) : FixedData(data, len) {

}
minter::pubkey_t minter::data::private_key::get_public_key(bool compressed) const {
    secp256k1_raii secp;
    secp256k1_pubkey pubkey;

    auto ret = secp256k1_ec_pubkey_create(secp.get(), &pubkey, cdata());

    uint8_t output_ser[65];
    memset(output_ser, 0, 65);
    size_t output_len = 65;

    unsigned int compFlag =
        compressed == ((uint8_t) 1) ? SECP256K1_EC_COMPRESSED : SECP256K1_EC_UNCOMPRESSED;

    if (ret) {
        int ret2 = secp256k1_ec_pubkey_serialize(secp.get(), output_ser, &output_len, &pubkey, compFlag);
        (void)ret2;
    }

    dev::bytes tmp(output_ser, output_ser + output_len);
    minter::pubkey_t out(tmp);

return out;
}

bool minter::data::private_key::operator==(const minter::data::private_key &other) const noexcept {
    return m_data == other.m_data;
}
bool minter::data::private_key::operator!=(const minter::data::private_key &other) const noexcept {
    return !(operator==(other));
}

std::string minter::data::private_key::to_string() const {
    return toHex();
}
minter::data::private_key::operator std::string() const {
    return to_string();
}
