/*
 * InstDisassembler.h
 *
 *  Created on: 2016/04/12
 *      Author: LittleBird
 */

#ifndef INSTDISASSEMBLER_H_
#define INSTDISASSEMBLER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include "InstDecoder.h"

namespace lb {

class InstDisassembler {
private:
    constexpr static int MAXN = 4096;

public:
    InstDisassembler();

    virtual ~InstDisassembler();

    void init(const unsigned* inst, const unsigned& len, const unsigned& pc);

    void start();

    void setUseLabel(bool useLabel);

    void setUseHex(bool useHex);

    unsigned length() const;

    std::string getLine(const unsigned& line) const;

private:
    int labelCount;
    bool useLabel;
    bool useHex;
    unsigned maxPc;
    unsigned len;
    unsigned inst[MAXN];
    std::vector<std::string> assembly;
    std::map<int, std::string> labelTable;
    std::string msg[MAXN];
    std::string result[MAXN];
};

} /* namespace lb */

#endif /* INSTDISASSEMBLER_H_ */
