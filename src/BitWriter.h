#include <fstream>
#ifndef BIT_WRITER_H
#define BIT_WRITER_H

struct BitFieldInfo {
	unsigned short length;
	unsigned char* code;
	BitFieldInfo() : length(0), code(nullptr) {}
	BitFieldInfo(unsigned char* code, unsigned short length) :
		length(length), code(code) {}
	bool operator==(BitFieldInfo& bit_field) {
		if (length != bit_field.length)
			return false;
		int number_of_bytes = (length + 7) / 8;
		for (int i = 0; i < number_of_bytes; ++i)
			if (code[i] != bit_field.code[i])
				return false;
		return true;
	}
};

class BitWriter {
private:
	size_t size, current_byte;
	char shift;
	unsigned char* buffer;
public:
	BitWriter(size_t size);

	~BitWriter() {
		delete buffer;
	}

	void Write(const BitFieldInfo& code);

	unsigned char* CreateCopyOfBuffer();

	char WriteToFile(std::ofstream& output_file);
};

#endif