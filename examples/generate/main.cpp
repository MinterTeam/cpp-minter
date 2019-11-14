/*!
 * minter.
 * generate_mnemonic.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>

#include <minter/bip39/Bip39Mnemonic.h>
#include <minter/address.h>
#include <minter/private_key.h>
#include <minter/public_key.h>

int main(int argc, char** argv) {

    int32_t n = 1;

    if(argc > 1) {
        try {
            n = std::stoi(argv[1]);
            if(n < 1) {
                throw std::invalid_argument("");
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << "unable to generate N mnemonics: invalid digit \"" << argv[1] << "\"" << std::endl;
            return 0xFF;
        }
    }

    std::stringstream out_buff;

    if(n > 10) {
        std::cout << "Processing...\n" << std::endl;
    }

    for(size_t i = 0; i < n; i++) {
        // generate english mnemonic with default parameters
        auto mnemonic = minter::Bip39Mnemonic::generate();

        // getting raw mnemonic phrase
        std::string mnemonic_phrase = mnemonic.raw;

        // getting private key from mnemonic (through making seed)
        minter::privkey_t priv_key = minter::privkey_t::from_mnemonic(mnemonic_phrase.c_str());

        // compressed 33 bytes
        minter::pubkey_t pub_key_comp = priv_key.get_public_key(true);
        // uncompressed 66 bytes, this variant must be used to get minter address
        minter::pubkey_t pub_key = priv_key.get_public_key(); // default: false - uncompressed

        // get minter address from uncompressed public key
        minter::address_t address = minter::address_t(pub_key);

        // or directly from private key
        minter::address_t address2 = minter::address_t(priv_key);

        out_buff << "Mnemonic: " << mnemonic_phrase << '\n';
        out_buff << "Priv Key: " << priv_key.to_hex() << '\n';
        out_buff << "Address : " << address.to_string() << '\n';
        out_buff << "|----------------------------------------------------|" << std::endl;
    }

    std::cout << out_buff.str() << std::endl;
    out_buff.clear();


    return 0;
}
 
 