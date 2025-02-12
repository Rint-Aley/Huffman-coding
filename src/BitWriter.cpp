#include "BitWriter.h"

BitWriter::BitWriter(size_t size) :
	size(size), current_byte(0), shift(0)
{
	buffer = new unsigned char[size];
	for (size_t i = 0; i < size; ++i) {
		buffer[i] = 0;
	}
}

void BitWriter::Write(const BitFieldInfo& code) {
	if (shift == 0) {
		char number_of_elem = (code.length - 1) / 8 + 1;
		for (unsigned char i = 0; i < number_of_elem; ++i) {
			buffer[current_byte++] = code.code[i];
		}
		shift = code.length % 8;
		if (shift != 0)
			--current_byte;
		return;
	}
	char offset = 8 - shift;
	buffer[current_byte] |= (code.code[0] << shift);
	if (shift + code.length < 8) {
		shift = (code.length + shift) % 8;
		return;
	}
	char last_elem = (code.length - 1) / 8;
	for (unsigned char i = 0; i < last_elem; ++i) {
		buffer[++current_byte] |= code.code[i] >> offset;
		buffer[current_byte] |= code.code[i + 1] << shift;
	}
	char new_shift = (code.length + shift) % 8;
	if (new_shift == 0) {
		shift = 0;
		++current_byte;
		return;
	}
	if (new_shift <= shift) {
		buffer[++current_byte] |= code.code[last_elem] >> offset;
	}
	shift = new_shift;
}

unsigned char* BitWriter::CreateCopyOfBuffer() {
	unsigned char* return_buffer = new unsigned char[size];
	for (size_t i = 0; i < size; ++i) {
		return_buffer[i] = buffer[i];
	}
	return return_buffer;
}

char BitWriter::WriteToFile(std::ofstream& output_file)
{
	if (!output_file.is_open())
		return 1;
	output_file.write(reinterpret_cast<char*>(buffer), size);
	if (output_file.fail())
		return 2;
	return 0;
}
