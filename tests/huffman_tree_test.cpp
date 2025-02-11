#include <gtest/gtest.h>
#include "../utils/huffman_tree.h"

bool is_equal_tree(HuffmanTree::Node *node1, HuffmanTree::Node *node2) {
	if (node1 == nullptr && node2 == nullptr)
		return true;
	if (node1 == nullptr || node2 == nullptr)
		return false;
	return *node1 == *node2 && is_equal_tree(node1->left, node2->left) && is_equal_tree(node1->right, node2->right);
}

TEST(HuffmanTree, Case1) {
	unsigned long long frequencies[BYTE_SIZE] = { 0 };
	frequencies[2] = 100;
	frequencies[3] = 12;
	frequencies[10] = 93;
	HuffmanTree huffman_tree = HuffmanTree(frequencies);
	HuffmanTree::Node *root = huffman_tree.get_root();

	HuffmanTree::Node prebuild_tree[5];
	prebuild_tree[0].left = &prebuild_tree[2];
	prebuild_tree[2].parent = &prebuild_tree[0];
	prebuild_tree[0].right = &prebuild_tree[1];
	prebuild_tree[1].parent = &prebuild_tree[0];

	prebuild_tree[0].freq = 205;

	prebuild_tree[1].left = &prebuild_tree[3];
	prebuild_tree[3].parent = &prebuild_tree[1];

	prebuild_tree[1].right = &prebuild_tree[4];
	prebuild_tree[4].parent = &prebuild_tree[1];

	prebuild_tree[1].freq = 105;

	prebuild_tree[2].data = 2;
	prebuild_tree[2].freq = 100;
	prebuild_tree[3].data = 3;
	prebuild_tree[3].freq = 12;
	prebuild_tree[4].data = 10;
	prebuild_tree[4].freq = 93;

	ASSERT_EQ(is_equal_tree(&prebuild_tree[0], root), true);
}