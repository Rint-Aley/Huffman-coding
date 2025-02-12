#include <fstream>
#include <iostream>
#include "encode.h"
#include "HuffmanTree.h"

void write_frequencies(std::ifstream& file, unsigned long long frequency[BYTE_SIZE]) {
    unsigned char data;
    while (file.good()) {
        file.read(reinterpret_cast<std::istream::char_type*>(&data), sizeof(data));
        if (file.eof()) {
            break;
        }
        ++frequency[data];
    }
}

void encode(char *input_file_name, char *output_file_name) {
    std::ifstream input_file(input_file_name, std::ios::binary);

    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return;
    }

    unsigned long long frequency[BYTE_SIZE] = {0};
    write_frequencies(input_file, frequency);

    input_file.close();

    HuffmanTree huffman_tree = HuffmanTree(frequency);
    
    // TODO: Getting Codes
    // TODO: Writing to the file
}