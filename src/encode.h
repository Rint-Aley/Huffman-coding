#ifndef ENCODE_H
#define ENCODE_H

#define BYTE_SIZE 256

#include "BitWriter.h"
#include "HuffmanTree.h"
#include <vector>

void encode(const char* input_file_name, const char* output_file_name, bool measure_perfomance = false);
void write_frequencies(std::vector<unsigned char>& data, unsigned long long frequency[BYTE_SIZE]);
void encode_huffman_tree(BitWriter& bit_writer, const HuffmanTree& tree);

#endif //ENCODE_H
