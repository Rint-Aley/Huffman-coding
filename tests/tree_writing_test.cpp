#include <gtest/gtest.h>
#include "../src/HuffmanTree.h"
#include "../src/BitWriter.h"
#include "../src/encode.h"

TEST(HuffmanTreeWriting, Case2) {
	unsigned long long frequencies[BYTE_SIZE] = { 0 };
	frequencies['a'] = 8;
	frequencies['b'] = 9;
	frequencies['c'] = 9;
	frequencies['d'] = 10;
	frequencies['e'] = 24;
	frequencies['f'] = 5;
	frequencies['g'] = 6;
	frequencies['h'] = 14;
	HuffmanTree huffman_tree = HuffmanTree(frequencies);

	BitWriter bw1(10); // 8 * 8 + 7 + 8 = 64 + 15 = 79
	//0001a1b01c1d01e001f1g1h
	encode_huffman_tree(bw1, huffman_tree);
	unsigned char* buffer_copy = bw1.CreateCopyOfBuffer();

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

	auto expectable_output = bw.CreateCopyOfBuffer();
	ASSERT_EQ(strncmp((char*)buffer_copy, (char*)expectable_output, 10), 0);
	delete zero.code;
	delete one.code;
	delete bfi.code;
}