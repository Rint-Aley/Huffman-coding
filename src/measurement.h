#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#define BYTE_SIZE 256
#include <string>
#include <chrono>
#include "BitWriter.h"
#include "HuffmanTree.h"

std::string size_in_bytes_to_stirng(size_t bytes);
std::string duration_to_string(std::chrono::duration<double>& duration);
size_t get_output_file_length_in_bits(BitFieldInfo** arr, unsigned long long* frequency);
inline size_t get_huffman_tree_length_in_bits(const HuffmanTree& huffman_tree) {
    return huffman_tree.get_number_of_nodes() + huffman_tree.get_number_of_leafs() * 8;
}

#endif