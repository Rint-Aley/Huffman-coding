#include <fstream>
#include <iostream>
#include "encode.h"
#include "HuffmanTree.h"
#include <vector>

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

size_t get_output_file_length_in_bits(BitFieldInfo **arr, unsigned long long *frequency) {
    size_t length = 0;
    for (int i = 0; i < BYTE_SIZE; ++i) {
        if (frequency[i] != 0)
            length += frequency[i] * (*arr[i]).length;
    }
    return length;
}

void encode(char *input_file_name, char *output_file_name) {
    std::ifstream input_file(input_file_name, std::ios::binary);

    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return;
    }

    unsigned long long frequency[BYTE_SIZE] = {0};
    write_frequencies(input_file, frequency);

    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

    input_file.close();

    std::ofstream output_file("output.bin", std::ios::binary);

    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    HuffmanTree huffman_tree = HuffmanTree(frequency);
    BitFieldInfo **codes = huffman_tree.convert_tree_to_bit_fields();
    
    size_t encoded_file_size_in_bits = get_output_file_length_in_bits(codes, frequency);
    unsigned char rest = encoded_file_size_in_bits % 8;
    int size_of_huffman_tree_in_bytes = (huffman_tree.get_number_of_nodes() + huffman_tree.get_bumber_of_leafs() * 8 + 7) / 8;
    size_t file_size_in_bytes = 2 + (encoded_file_size_in_bits + 7) / 8 + size_of_huffman_tree_in_bytes;

    BitWriter bw(file_size_in_bytes);
    // The number of significant bits in the last byte of file
    bw.Write(BitFieldInfo(&rest, 8));
    // The number of leafs in huffman tree
    unsigned char leafs = huffman_tree.get_bumber_of_leafs() - 1;
    bw.Write(BitFieldInfo(&leafs, 8));

    // TODO: Writing Huffman tree to the file
    
    for (size_t i = 0; i < buffer.size(); ++i) {
        bw.Write(*codes[buffer[i]]);
    }
    if (bw.WriteToFile(output_file) == 2) {
        std::cerr << "Failed to write to output file." << std::endl;
    }
    output_file.close();
}