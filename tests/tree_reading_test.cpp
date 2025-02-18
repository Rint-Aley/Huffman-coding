#include <gtest/gtest.h>

#include "../src/BitReader.h"
#include "../src/HuffmanTree.h"
#include "../src/BitWriter.h"
#include "../src/decode.h"
#include "../src/encode.h"

void collect_huffman_leaves(const HuffmanTree::Node* node, std::vector<unsigned char>& leaves) {
    if (!node)
        return;
    if (node->is_leaf())
        leaves.push_back(node->data);
    else {
        collect_huffman_leaves(node->left, leaves);
        collect_huffman_leaves(node->right, leaves);
    }
}

TEST(HuffmanTreeReading, Case1) {
    BitWriter bw(10);
    BitFieldInfo zero(new unsigned char(0), 1), one(new unsigned char(1), 1), bfi(new unsigned char('a'), 8);
    for (int i = 0; i < 3; ++i)
        bw.Write(zero);
    bw.Write(one);
    bw.Write(bfi);
    bfi.code[0] = 'b';
    bw.Write(one);
    bw.Write(bfi);
    bfi.code[0] = 'c';
    bw.Write(zero);
    bw.Write(one);
    bw.Write(bfi);
    bfi.code[0] = 'd';
    bw.Write(one);
    bw.Write(bfi);
    bfi.code[0] = 'e';
    bw.Write(zero);
    bw.Write(one);
    bw.Write(bfi);
    bfi.code[0] = 'f';
    bw.Write(zero);
    bw.Write(zero);
    bw.Write(one);
    bw.Write(bfi);
    bfi.code[0] = 'g';
    bw.Write(one);
    bw.Write(bfi);
    bfi.code[0] = 'h';
    bw.Write(one);
    bw.Write(bfi);

    unsigned char* buffer = bw.CreateCopyOfBuffer();
    size_t total_bits = 79;
    size_t buffer_size = 10;

    BitReader br(buffer, buffer_size, total_bits);

    HuffmanTree::Node* tree = decode_huffman_tree(br);
    ASSERT_NE(tree, nullptr);


    std::vector<unsigned char> leaves;
    collect_huffman_leaves(tree, leaves); // left-to-right

    const std::vector<unsigned char> expected = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    EXPECT_EQ(leaves, expected);

    delete tree;
    delete[] buffer;
    delete zero.code;
    delete one.code;
    delete bfi.code;
}