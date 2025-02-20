#include "measurement.h"
#include <string>
#include <chrono>
#include <format>
#include "BitWriter.h"

std::string size_in_bytes_to_stirng(size_t bytes)
{
	if (bytes > 1024 * 1024 * 1024)
		return std::format("{:.2f} GB", static_cast<float>(bytes) / 1024 / 1024 / 1024);
	if (bytes > 1024 * 1024)
		return std::format("{:.2f} MB", static_cast<float>(bytes) / 1024 / 1024);
	if (bytes > 1024)
		return std::format("{:.2f} KB", static_cast<float>(bytes) / 1024);
	else
		return std::format("{} Bytes", bytes);
}

std::string duration_to_string(std::chrono::duration<double>& duration)
{
	if (duration.count() < 1)
		return std::format("{} ms", static_cast<int>(duration.count() * 1000));

	const size_t seconds = duration.count();
	if (seconds < 60)
		return std::format("{} s", seconds);
	if (seconds < 3600)
		return std::format("{} m {} s", seconds / 60, seconds % 60);
	else
		return std::format("{} h {} m {} s", seconds / 3600, (seconds % 3600) / 60, seconds % 60);
}

size_t get_output_file_length_in_bits(BitFieldInfo** arr, unsigned long long* frequency) {
	size_t length = 0;
	for (int i = 0; i < BYTE_SIZE; ++i) {
		if (frequency[i] != 0)
			length += frequency[i] * (*arr[i]).length;
	}
	return length;
}

