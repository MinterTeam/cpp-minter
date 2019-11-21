/*!
 * minter_tx.
 * common.cpp
 *
 * \date 11/21/2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <map>
#include <string>
#include "minter/eth/common.h"

std::string dev::escaped(std::string const& _s, bool _all)
{
    static const std::map<char, char> prettyEscapes{{'\r', 'r'}, {'\n', 'n'}, {'\t', 't'}, {'\v', 'v'}};
    std::string ret;
    ret.reserve(_s.size() + 2);
    ret.push_back('"');
    for (auto i: _s)
        if (i == '"' && !_all)
            ret += "\\\"";
        else if (i == '\\' && !_all)
            ret += "\\\\";
        else if (prettyEscapes.count(i) && !_all)
        {
            ret += '\\';
            ret += prettyEscapes.find(i)->second;
        }
        else if (i < ' ' || _all)
        {
            ret += "\\x";
            ret.push_back("0123456789abcdef"[(uint8_t)i / 16]);
            ret.push_back("0123456789abcdef"[(uint8_t)i % 16]);
        }
        else
            ret.push_back(i);
    ret.push_back('"');
    return ret;
}