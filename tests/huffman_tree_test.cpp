#include <gtest/gtest.h>
#include "../src/HuffmanTree.h"
#include "../src/BitWriter.h"

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
	auto arr = huffman_tree.convert_tree_to_bit_fields();
	ASSERT_EQ(*arr[2] == BitFieldInfo(new unsigned char(0b0), 1), true);
	ASSERT_EQ(*arr[3] == BitFieldInfo(new unsigned char(0b01), 2), true);
	ASSERT_EQ(*arr[10] == BitFieldInfo(new unsigned char(0b11), 2), true);
}

TEST(HuffmanTree, Case2) {
	unsigned long long frequencies[BYTE_SIZE] = { 0 };
	frequencies[2] = 8;
	frequencies[3] = 9;
	frequencies[10] = 9;
	frequencies[23] = 10;
	frequencies[52] = 24;
	frequencies[121] = 5;
	frequencies[193] = 6;
	frequencies[234] = 14;
	HuffmanTree huffman_tree = HuffmanTree(frequencies);

	HuffmanTree::Node *prebuild_tree[15];
	prebuild_tree[0] = &HuffmanTree::Node(2, 8);
	prebuild_tree[1] = &HuffmanTree::Node(3, 9);
	prebuild_tree[2] = &HuffmanTree::Node(10, 9);
	prebuild_tree[3] = &HuffmanTree::Node(23, 10);
	prebuild_tree[4] = &HuffmanTree::Node(52, 24);
	prebuild_tree[5] = &HuffmanTree::Node(121, 5);
	prebuild_tree[6] = &HuffmanTree::Node(193, 6);
	prebuild_tree[7] = &HuffmanTree::Node(234, 14);

	prebuild_tree[8] = &HuffmanTree::Node(0, 17);
	prebuild_tree[8]->left = prebuild_tree[0];
	prebuild_tree[8]->right = prebuild_tree[1];

	prebuild_tree[9] = &HuffmanTree::Node(0, 19);
	prebuild_tree[9]->left = prebuild_tree[2];
	prebuild_tree[9]->right = prebuild_tree[3];
	
	prebuild_tree[10] = &HuffmanTree::Node(0, 11);
	prebuild_tree[10]->left = prebuild_tree[5];
	prebuild_tree[10]->right = prebuild_tree[6];

	prebuild_tree[11] = &HuffmanTree::Node(0, 25);
	prebuild_tree[11]->left = prebuild_tree[10];
	prebuild_tree[11]->right = prebuild_tree[7];

	prebuild_tree[12] = &HuffmanTree::Node(0, 49);
	prebuild_tree[12]->left = prebuild_tree[4];
	prebuild_tree[12]->right = prebuild_tree[11];

	prebuild_tree[13] = &HuffmanTree::Node(0, 36);
	prebuild_tree[13]->left = prebuild_tree[8];
	prebuild_tree[13]->right = prebuild_tree[9];

	prebuild_tree[14] = &HuffmanTree::Node(0, 85);
	prebuild_tree[14]->left = prebuild_tree[13];
	prebuild_tree[14]->right = prebuild_tree[12];

	ASSERT_EQ(is_equal_tree(huffman_tree.get_root(), prebuild_tree[14]), true);
	
	auto arr = huffman_tree.convert_tree_to_bit_fields();

	ASSERT_EQ(*arr[2] == BitFieldInfo(new unsigned char(0b000), 3), true);
	ASSERT_EQ(*arr[3] == BitFieldInfo(new unsigned char(0b100), 3), true);
	ASSERT_EQ(*arr[10] == BitFieldInfo(new unsigned char(0b010), 3), true);
	ASSERT_EQ(*arr[23] == BitFieldInfo(new unsigned char(0b110), 3), true);
	ASSERT_EQ(*arr[52] == BitFieldInfo(new unsigned char(0b01), 2), true);
	ASSERT_EQ(*arr[121] == BitFieldInfo(new unsigned char(0b0011), 4), true);
	ASSERT_EQ(*arr[193] == BitFieldInfo(new unsigned char(0b1011), 4), true);
	ASSERT_EQ(*arr[234] == BitFieldInfo(new unsigned char(0b111), 3), true);
}