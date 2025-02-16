#include <fstream>
#include <iostream>
#include "encode.h"
#include "HuffmanTree.h"
#include <vector>

void write_frequencies(std::vector<unsigned char>& data, unsigned long long frequency[BYTE_SIZE]) {
    for (size_t i = 0; i < data.size(); ++i) {
        ++frequency[data[i]];
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

inline size_t get_huffman_tree_length_in_bits(const HuffmanTree& huffman_tree) {
    return huffman_tree.get_number_of_nodes() + huffman_tree.get_number_of_leafs() * 8;
}

void encode(char *input_file_name, char *output_file_name) {
    std::ifstream input_file(input_file_name, std::ios::binary);

    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return;
    }
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();

    unsigned long long frequency[BYTE_SIZE] = {0};
    write_frequencies(buffer, frequency);

    std::ofstream output_file(output_file_name, std::ios::binary);

    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    HuffmanTree huffman_tree = HuffmanTree(frequency);
    BitFieldInfo **codes = huffman_tree.convert_tree_to_bit_fields();
    
    size_t encoded_file_size_in_bits = get_output_file_length_in_bits(codes, frequency) + get_huffman_tree_length_in_bits(huffman_tree);
    unsigned char rest = encoded_file_size_in_bits % 8;
    size_t file_size_in_bytes = 2 + (encoded_file_size_in_bits + 7) / 8;

    BitWriter bw(file_size_in_bytes);
    // The number of significant bits in the last byte of file
    bw.Write(BitFieldInfo(&rest, 8));
    unsigned char number_of_letters_substracted_by_one = huffman_tree.get_number_of_leafs() - 1;
    bw.Write(BitFieldInfo(&number_of_letters_substracted_by_one, 8));

    encode_huffman_tree(bw, huffman_tree);
    
    for (size_t i = 0; i < buffer.size(); ++i) {
        bw.Write(*codes[buffer[i]]);
    }
    if (bw.WriteToFile(output_file) == 2) {
        std::cerr << "Failed to write to output file." << std::endl;
    }
    output_file.close();
}

void encode_huffman_tree(BitWriter& bit_writer, const HuffmanTree& tree) {
    HuffmanTree::Node *current_node = tree.get_root();
    
    unsigned char one_c = 1, zero_c = 0, letter_code;
    BitFieldInfo one(&one_c, 1), zero(&zero_c, 1), letter(&letter_code, 8);
    if (current_node == nullptr)
        return;
    if (current_node->is_leaf()) {
        bit_writer.Write(one);
        bit_writer.Write(BitFieldInfo(&current_node->data, 8));
        return;
    }
    while (true) {
        bit_writer.Write(zero);
        while (!current_node->left->is_leaf()) {
            current_node = current_node->left;
            bit_writer.Write(zero);
        }
        letter_code = current_node->left->data;
        bit_writer.Write(one);
        bit_writer.Write(letter);
        if (!current_node->right->is_leaf()) {
            current_node = current_node->right;
            continue;
        }
        letter_code = current_node->right->data;
        bit_writer.Write(one);
        bit_writer.Write(letter);
        // Depend on the written code in buffer, we return back to parents until reach element with 0 bit
        while (true) {
            if (current_node->parent == nullptr)
                return;
            if (current_node->parent->right == current_node && current_node->parent->parent == nullptr)
                return;
            else if (current_node->parent->right == current_node) {
                current_node = current_node->parent;
            }
            else if (current_node->parent->left == current_node && current_node->parent->right->is_leaf()) {
                current_node = current_node->parent;
                letter_code = current_node->right->data;
                bit_writer.Write(one);
                bit_writer.Write(letter);
            }
            else if (current_node->parent->left == current_node) {
                current_node = current_node->parent->right;
                break;
            }
        }
    }
}