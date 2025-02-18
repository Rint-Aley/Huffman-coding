#include "decode.h"

#include <chrono>
#include <iostream>

#include "measurement.h"

HuffmanTree::Node* decode_huffman_tree(BitReader &br) {
    int bit;
    if (!br.readBit(bit))
        return nullptr;
    if (bit == 1) {
        unsigned int letter;
        if (!br.readBits(8, letter))
            return nullptr;
        auto* node = new HuffmanTree::Node();
        node->data = static_cast<unsigned char>(letter);
        node->freq = 0;
        node->left = node->right = node->parent = nullptr;
        return node;
    }
    auto* node = new HuffmanTree::Node();
    node->left = decode_huffman_tree(br);
    node->right = decode_huffman_tree(br);
    node->freq = 0;
    node->data = 0;
    node->parent = nullptr;
    return node;
}

void decode(char *input_file_name, char *output_file_name, bool measure_performance) {
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream input_file(input_file_name, std::ios::binary);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return;
    }
    std::vector<unsigned char> buffer((std::istreambuf_iterator(input_file)), std::istreambuf_iterator<char>());
    input_file.close();

    if (buffer.size() < 2) {
        std::cerr << "Failed to decode Huffman tree." << std::endl;
        return;
    }

    unsigned char rest = buffer[0];

    size_t data_bytes = buffer.size() - 2;
    size_t total_bits;
    if (rest == 0)
        total_bits = data_bytes * 8;
    else
        total_bits = (data_bytes - 1) * 8 + rest;

    BitReader br(buffer.data() + 2, data_bytes, total_bits);

    HuffmanTree::Node* root = decode_huffman_tree(br);
    if (root == nullptr) {
        std::cerr << "Failed to decode Huffman tree." << std::endl;
        return;
    }

    std::vector<unsigned char> decoded_data;
    while (br.bitsRemaining() > 0) {
        HuffmanTree::Node* current = root;
        while (!current->is_leaf()) {
            int bit;
            if (!br.readBit(bit))
                break;
            if (bit == 0)
                current = current->left;
            else
                current = current->right;
        }
        if (current == nullptr)
            break;
        decoded_data.push_back(current->data);
    }

    std::ofstream output_file(output_file_name, std::ios::binary);
    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        delete root;
        return;
    }
    output_file.write(reinterpret_cast<char*>(decoded_data.data()), static_cast<long long>(decoded_data.size()));
    output_file.close();

    if (measure_performance) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double>(end - start);
        std::cout << "Decoding took: " << duration_to_string(duration);
    }

    delete root;
}
