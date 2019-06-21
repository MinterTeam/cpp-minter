/*!
 * minter.
 * generate_mnemonic.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <minter/bip39/Bip39Mnemonic.h>
#include <minter/address.h>
#include <minter/private_key.h>
#include <minter/public_key.h>

int main() {
    // generate english mnemonic with default parameters
    auto mnemonic = minter::Bip39Mnemonic::generate();

    // getting raw mnemonic phrase
    std::string mnemonic_phrase = mnemonic.raw;

    // getting private key from mnemonic (through making seed)
    minter::privkey_t priv_key = minter::privkey_t::from_mnemonic(data.mnemonic.c_str());

    // compressed 33 bytes
    minter::pubkey_t pub_key = priv_key.get_public_key(true);
    // uncompressed 66 bytes, this variant must be used to get minter address
    minter::pubkey_t pub_key = priv_key.get_public_key(); // default: false - uncompressed

    // get minter address from uncompressed public key
    minter::address_t address = minter::address_t(pub_key);

    // or directly from private key
    minter::address_t address2 = minter::address_t(priv_key);



    return 0;
}
 
 