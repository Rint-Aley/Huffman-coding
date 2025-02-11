#ifndef ENCODE_H
#define ENCODE_H

#define BYTE_SIZE 256

void write_frequencies(std::ifstream& file, unsigned long long frequency[BYTE_SIZE]);
void encode(char* input_file_name, char* output_file_name);

#endif //ENCODE_H
