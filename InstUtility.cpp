/*
 * InstUtility.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstUtility.h"

namespace lb {

bool isValidArguments(int& argc, char**& argv) {
    if (argc < 2 || argc > 5) {
        return false;
    }
    bool hasA = false;
    bool hasD = false;
    bool hasOutput = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-d" || std::string(argv[i]) == "-D") {
            hasD = true;
        }
        if (std::string(argv[i]) == "-a" || std::string(argv[i]) == "-A") {
            hasA = true;
        }
    }
    if (hasA == hasD) {
        return false;
    }
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "-O") {
            hasOutput = true;
        }
    }
    if (hasOutput) {
        return argc >= 4 && argc <= 5;
    }
    else {
        return argc >= 2 && argc <= 3;
    }
}

AssemblerArgumentInfo processArguments(int& argc, char**& argv) {
    if (!isValidArguments(argc, argv)) {
        return AssemblerArgumentInfo();
    }
    AssemblerArgumentInfo ret;
    bool usedArguments[10] = { false } ;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-a" || std::string(argv[i]) == "-A") {
            ret.hasA = true;
            usedArguments[i] = true;
        }
        if (std::string(argv[i]) == "-d" || std::string(argv[i]) == "-D") {
            ret.hasD = true;
            usedArguments[i] = true;
        }
        if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "-O") {
            ret.hasOutputFile = true;
            usedArguments[i] = true;
            if (i + 1 < argc) {
                ret.outputFile = argv[i + 1];
                usedArguments[i + 1] = true;
            }
            else {
                return AssemblerArgumentInfo();
            }
        }
    }
    for (int i = 1; i < argc; ++i) {
        if (!usedArguments[i]) {
            ret.hasInputFile = true;
            ret.inputFile = argv[i];
            usedArguments[i] = true;
        }
    }
    ret.isValid = true;
    return ret;
}

int toSigned(const unsigned& src) {
    return static_cast<int>(src);
}

int toSigned(const unsigned& src, const InstMemLen& type) {
    if (type == InstMemLen::WORD) {
        return static_cast<int>(src);
    }
    else if (type == InstMemLen::HALF) {
        int var = static_cast<int>(src << 16);
        int ret = var >> 16;
        return ret;
    }
    else {
        int var = static_cast<int>(src << 24);
        int ret = var >> 24;
        return ret;
    }
}

int toSigned(const unsigned& src, const int& bits) {
    int var = static_cast<int>(src << (32 - bits));
    int ret = var >> (32 - bits);
    return ret;
}

unsigned toUnsigned(const int& src) {
    return static_cast<unsigned>(src);
}

unsigned getBitsInRange(const unsigned& src, const int& l, const int& r) {
    return (src << (32 - r)) >> (l + (32 - r));
}

} /* namespace lb */
