#ifndef BIT_READER_H
#define BIT_READER_H

#include <cstdlib>

class BitReader {
    const unsigned char* buffer;
    size_t byte_length;
    size_t current_byte;
    int bit_index;
    size_t bits_read;
    size_t total_bits;

public:
    BitReader(const unsigned char* buffer, size_t byte_length, size_t total_bits);

    bool readBit(int &bit);

    bool readBits(int count, unsigned int &value);

    [[nodiscard]] size_t bitsRemaining() const;
};



#endif //BIT_READER_H
