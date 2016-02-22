#ifndef __UTIL_H__
#define __UTIL_H__

// Return bit n of vector.
static inline int bit(uint32_t vector, int n) {
    return (vector >> n) & 1;
}

// Set byte n of vector to val.
static inline uint32_t set_byte(uint32_t vector, int n, uint8_t val) {
	return (vector & ~(0xFF << (8*n))) | (val << (8*n));
}

// Return byte n of vector.
static inline uint8_t get_byte(uint32_t vector, int n) {
    return (vector >> (8*n)) & 0xFF;
}

extern const uint64_t m1; // binary: 0101...
extern const uint64_t m2; // binary: 00110011..
extern const uint64_t m4; // binary:  4 zeros,  4 ones ...
extern const uint64_t h01; // the sum of 256 to the power of 0,1,2,3...

// Return the number of bits in x that are 1.
static inline int popcount(uint64_t x) {
    x -= (x >> 1) & m1;         // put count of each 2 bits into those 2 bits
    x = (x & m2) + ((x >> 2) & m2); // put count of each 4 bits into those 4 bits
    x = (x + (x >> 4)) & m4;        // put count of each 8 bits into those 8 bits
    return (x * h01) >> 56;  // returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ...
}


void print_word(uint32_t word);

#endif//__UTIL_H__
