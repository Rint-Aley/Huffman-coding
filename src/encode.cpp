#include <algorithm>
#include <fstream>
#include <iostream>
#include "encode.h"
#include <unordered_map>
#include "../utils/huffman_tree.h"


void encode(char *in, char *out) {
    std::ifstream fr(in, std::ios::binary);

    if (!fr.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    long long counts[CODE_SIZE] = {0};
    unsigned char data;
    while (fr.good()) {
        fr.read(reinterpret_cast<std::istream::char_type *>(&data), sizeof(data));
        if (fr.eof()) {
            break;
        }
        ++counts[data];
    }

    unsigned char arr[CODE_SIZE] = {};
    long long freq[CODE_SIZE] = {};
    int index = 0;
    for (int i = 0; i < CODE_SIZE; ++i) {
        if (counts[i] != 0) {
            arr[index] = i;
            freq[index] = counts[i];
            ++index;
        }
    }
    for (int i = 0; i < index; ++i) {
        std::cout << +arr[i] << ' ' << freq[i] << std::endl;
    }
    std::cout << std::endl;


    HuffmanTree huffman_tree = HuffmanTree(CODE_SIZE * 4);
    std::unordered_map<unsigned char, std::string> codes;

    huffman_tree.build(arr, freq, index);
    huffman_tree.get_codes(codes);

    for (auto &[key, value]: codes) {
        std::cout << +key << ' ' << value << std::endl;
    }
    HuffmanTree::Node *root = huffman_tree.get_huffman_tree();

    fr.close();
}