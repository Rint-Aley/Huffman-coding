#include <filesystem>
#include <iostream>
#include "analyze.h"
#include "measurement.h"
#include "encode.h"
#include "decode.h"

void analyze_in_dir(char *input_dir) {
    std::ofstream outFile(DEST);
    std::filesystem::path p(TEMP);

    if (!outFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи" << std::endl;
        return;
    }
    outFile << "Исходный размер\t После сжатия\tКоэффициент сжатия\tВремя сжатия\tРазжатия\tТип файла\n";
    for (const auto &entry: std::filesystem::directory_iterator(input_dir)) {
        if(entry.is_directory())
            continue;
        auto start = std::chrono::high_resolution_clock::now();
        encode(entry.path().string().data(), TEMP, true);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double>(end - start);

        auto size = entry.file_size();
        auto size_compressed = std::filesystem::file_size(p);
        auto ratio = std::format("{:.2f}", static_cast<double>( size) / size_compressed);

        outFile << size_in_bytes_to_stirng(size) << "\t" << size_in_bytes_to_stirng(size_compressed) << '\t'
                << ratio << '\t' << duration_to_string(duration) << '\t';

        start = std::chrono::high_resolution_clock::now();
        decode(TEMP, entry.path().string().data(), true);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration<double>(end - start);

        outFile << duration_to_string(duration) << '\t' << entry.path().extension() <<'\n';
    }
    try {
        std::filesystem::remove(TEMP);
    }
    catch(const std::filesystem::filesystem_error& err) {
        std::cout << "filesystem error: " << err.what() << '\n';
    }
}