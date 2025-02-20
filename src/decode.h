#ifndef DECODE_H
#define DECODE_H

#include "BitReader.h"
#include "HuffmanTree.h"

void decode(const char* input_file_name, const char* output_file_name, bool measure_performance = false);
HuffmanTree::Node* decode_huffman_tree(BitReader &br);


#endif //DECODE_H
