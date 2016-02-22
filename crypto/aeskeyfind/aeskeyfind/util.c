#include <stdio.h>
#include <stdint.h>

#include "util.h"

const uint64_t m1  = 0x5555555555555555LL; // binary: 0101...
const uint64_t m2  = 0x3333333333333333LL; // binary: 00110011..
const uint64_t m4  = 0x0f0f0f0f0f0f0f0fLL; // binary:  4 zeros,  4 ones ...
const uint64_t h01 = 0x0101010101010101LL; // the sum of 256 to the power of 0,1,2,3...

// Print a word in order byte0 byte1 byte2 byte3
void print_word(uint32_t word) {
    for (int byte = 0; byte < 4; byte++)
        printf("%02x",get_byte(word,byte));
}

