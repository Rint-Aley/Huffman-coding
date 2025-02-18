#include "BitReader.h"

BitReader::BitReader(const unsigned char* buffer, size_t byte_length, size_t total_bits)
    : buffer(buffer), byte_length(byte_length), current_byte(0), bit_index(0), bits_read(0), total_bits(total_bits)
{
}

bool BitReader::readBit(int &bit) {
    if (bits_read >= total_bits)
        return false;
    bit = (buffer[current_byte] >> bit_index) & 1;
    bit_index++;
    bits_read++;
    if (bit_index == 8) {
        bit_index = 0;
        current_byte++;
    }
    return true;
}

bool BitReader::readBits(const int count, unsigned int &value) {
    value = 0;
    for (int i = 0; i < count; i++) {
        int bit;
        if (!readBit(bit))
            return false;
        value |= bit << i;
    }
    return true;
}

size_t BitReader::bitsRemaining() const {
    return total_bits - bits_read;
}