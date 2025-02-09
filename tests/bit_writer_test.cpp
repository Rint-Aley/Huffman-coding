#include <gtest/gtest.h>
#include "../src/bit_writer.h"

TEST(BitWriter, WriteBytes) {
	unsigned char char_code[3] = { 0b00110011 };
	BitFieldInfo code = BitFieldInfo(char_code, 8);
	BitWriter bw(5);
	bw.Write(code);
	code.code[0] = 0b01001100;
	code.code[1] = 0b11101100;
	code.code[2] = 0b00110000;
	code.length = 24;
	bw.Write(code);
	code.code[0] = 0b00000111;
	code.length = 8;
	bw.Write(code);
	unsigned char* copy = bw.CreateCopyOfBuffer();
	ASSERT_EQ(copy[0], 0b00110011);
	ASSERT_EQ(copy[1], 0b01001100);
	ASSERT_EQ(copy[2], 0b11101100);
	ASSERT_EQ(copy[3], 0b00110000);
	ASSERT_EQ(copy[4], 0b00000111);
}

TEST(BitWriter, WriteBits) {
	unsigned char char_code[1] = { 0b001 };
	BitFieldInfo code = BitFieldInfo(char_code, 3);
	BitWriter bw(3);
	bw.Write(code);
	code.code[0] = 0b010;
	code.length = 3;
	bw.Write(code);
	bw.Write(code);
	bw.Write(code);
	code.code[0] = 0b1;
	code.length = 1;
	for (int i = 0; i < 8; ++i)
		bw.Write(code);
	unsigned char* copy = bw.CreateCopyOfBuffer();
	ASSERT_EQ(copy[0], 0b10010001);
	ASSERT_EQ(copy[1], 0b11110100);
	ASSERT_EQ(copy[2], 0b00001111);
}

TEST(BitWriter, BigChunks) {
	unsigned char char_code[4] = { 0b00110011, 0b00111011, 0b101, 0};
	BitFieldInfo code = BitFieldInfo(char_code, 19);
	BitWriter bw(8);
	bw.Write(code);
	code.code[0] = 0b01001100;
	code.code[1] = 0b11101100;
	code.code[2] = 0b00110000;
	code.code[3] = 0b101;
	code.length = 27;
	bw.Write(code);
	code.code[0] = 0b10010100;
	code.code[1] = 0b10101110;
	code.code[2] = 0b11;
	code.length = 18;
	bw.Write(code);
	unsigned char* copy = bw.CreateCopyOfBuffer();
	ASSERT_EQ(copy[0], 0b00110011);
	ASSERT_EQ(copy[1], 0b00111011);
	ASSERT_EQ(copy[2], 0b01100101);
	ASSERT_EQ(copy[3], 0b01100010);
	ASSERT_EQ(copy[4], 0b10000111);
	ASSERT_EQ(copy[5], 0b00101001);
	ASSERT_EQ(copy[6], 0b10100101);
	ASSERT_EQ(copy[7], 0b11101011);
}

TEST(BitWriter, WriteDifferentPatterns) {
	unsigned char char_code[3] = { 0b00110011 };
	BitFieldInfo code = BitFieldInfo(char_code, 8);
	BitWriter bw(5);
	bw.Write(code);
	code.code[0] = 0b01001;
	code.length = 5;
	bw.Write(code);
	code.code[0] = 0b110111;
	code.length = 6;
	bw.Write(code);
	code.code[0] = 0b00000111;
	code.code[1] = 0b11111000;
	code.code[2] = 0b111;
	code.length = 19;
	bw.Write(code);
	unsigned char* copy = bw.CreateCopyOfBuffer();
	ASSERT_EQ(copy[0], 0b00110011);
	ASSERT_EQ(copy[1], 0b11101001);
	ASSERT_EQ(copy[2], 0b00111110);
	ASSERT_EQ(copy[3], 0b11000000);
	ASSERT_EQ(copy[4], 0b00111111);
}