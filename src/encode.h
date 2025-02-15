#ifndef ENCODE_H
#define ENCODE_H

#define BYTE_SIZE 256

#include "BitWriter.h"
#include "HuffmanTree.h"

void write_frequencies(std::ifstream& file, unsigned long long frequency[BYTE_SIZE]);
void encode(char* input_file_name, char* output_file_name);
size_t get_output_file_length_in_bits(BitFieldInfo** arr, unsigned long long* frequency);
void encode_huffman_tree(BitWriter& bit_writer, const HuffmanTree& tree);

#endif //ENCODE_H
