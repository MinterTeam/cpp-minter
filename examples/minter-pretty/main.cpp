/*!
 * minter-tx.
 *
 * \date 12.06.2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include <atomic>
#include <bip3x/HDKeyEncoder.h>
#include <boost/program_options.hpp>
#include <chrono>
#include <minter/private_key.h>
#include <minter/tx.hpp>
#include <mutex>
#include <queue>
#include <thread>
#include <toolbox/strings.hpp>
#include <toolbox/strings/regex.h>

enum search_logic {
    start,
    end,
    both
};

namespace po = boost::program_options;

int main(int argc, char** argv) {
    std::vector<std::string> wordlist = {
        "abba",
        "face",
        "cafe",
        "cafe",
        "fade",
        "feed",
        "beef",
        "dead",
        "added",
        "decaf",
        "faded",
        "decade",
        "facade",
        "deadbeef",
    };

    po::options_description desc("Minter Beauty Address Generator");
    desc.add_options()("help", "print this help");

    desc.add_options()(
        "word", po::value<std::string>(), "Word to search")(
        "nodict", "Exclude default dictionary")(
        "whence", po::value<std::string>(), "Where to search word: start, end or both (any of side)");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    std::string word;
    if (vm.count("word")) {
        word = vm.at("word").as<std::string>();
        if (!toolbox::strings::matches_pattern("^[0-9a-fA-F]+$", word)) {
            std::cerr << "Invalid word: must contain only digits and symbols from \"a\" to \"f\" (case insensitive)\n";
            return 1;
        }
    }

    if (vm.count("nodict")) {
        if (word.empty()) {
            std::cerr << "If you're using 'nodict' parameter, you must specify --word to search with\n";
            return 0;
        }
        wordlist.clear();
        wordlist.push_back(word);
    } else if (!word.empty()) {
        wordlist.clear();
        wordlist.push_back(word);
    }

    search_logic logic = start;
    if (vm.count("whence")) {
        std::string logic_arg = vm.at("whence").as<std::string>();
        if (toolbox::strings::equals_icase(logic_arg, "start")) {
            logic = start;
        } else if (toolbox::strings::equals_icase(logic_arg, "end")) {
            logic = end;
        } else if (toolbox::strings::equals_icase(logic_arg, "both")) {
            logic = both;
        } else {
            std::cerr << "Invalid logic argument: must be one of: start, end or both\n";
            return 1;
        }
    }

    std::atomic_bool found(false);
    std::atomic<size_t> iterated(0);
    std::mutex out_lock;
    std::mutex gen_lock;

    uint32_t conc = std::thread::hardware_concurrency();
    std::cout << "Starting concurrently: " << conc << std::endl;

    auto comparator = [&logic](const std::string& item, const std::string& word) {
        if (logic == start) {
            return toolbox::strings::equals_icase(item.substr(0, word.length()), word);
        } else if (logic == end) {
            return toolbox::strings::equals_icase(item.substr(item.length() - word.length(), word.length()), word);
        } else {
            return toolbox::strings::equals_icase(item.substr(0, word.length()), word) || toolbox::strings::equals_icase(item.substr(item.length() - word.length(), word.length()), word);
        }
    };

    std::vector<std::thread> threads;
    for (size_t i = 0; i < conc; i++) {
        auto t = std::thread([&iterated, &found, &wordlist, &comparator, &out_lock, &gen_lock]() {
            while (!found) {

                bip3x::Bip39Mnemonic::MnemonicResult mnem = bip3x::Bip39Mnemonic::generate();
                minter::privkey_t pk;
                minter::address_t address;
                {
                    std::lock_guard<std::mutex> lock(gen_lock);
                    pk = minter::privkey_t::from_mnemonic(mnem.raw);
                    address = minter::address_t(pk.get_public_key());
                }

                const std::string item = address.to_string_no_prefix();
                for (const auto& word : wordlist) {
                    if (comparator(item, word)) {
                        {
                            std::lock_guard<std::mutex> l(out_lock);
                            std::cout << std::endl;
                            std::cout << "Found: " << address.to_string() << '\n';
                            std::cout << mnem.raw << '\n';
                            std::cout << std::endl;
                        }

                        found = true;

                        return;
                    }
                }

                {
                    std::lock_guard<std::mutex> lock(out_lock);
                    std::cout << "\rCompared: " << iterated << std::flush;
                }
                iterated++;
            }
        });
        threads.push_back(std::move(t));
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

    while (!found) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    for (auto&& t : threads) {
        t.join();
    }

    return 0;
}
