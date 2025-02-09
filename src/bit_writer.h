#ifndef BIT_WRITER_H
#define BIT_WRITER_H

struct BitFieldInfo {
	unsigned short length;
	unsigned char* code;
	BitFieldInfo(unsigned char* code, unsigned short length) :
		length(length),	code(code) 
	{}
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
};

#endif