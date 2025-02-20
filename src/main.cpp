#include <iostream>
#include "cli.h"
#include "decode.h"
#include "encode.h"
#include "measurement.h"
#include "analyze.h"

int main(int argc, char** argv) {
    const char* HELP_MESSAGE = "executable_name [-h] [--help] - shows this message\n"
        "executable_name encode <source_file> <output_file> - encodes source file and writes it in output file\n"
        "executable_name decode <source_file> <output_file> - decodes encrypted source file and writes it in output file"
        "executable_name analyze <source_dir> - write statistic in out.txt for each file in <source_dir>";
    switch (parse_args(argc, const_cast<const char**>(argv))) {
    case Status::NoArgs:
        std::cout << HELP_MESSAGE << std::endl;
        break;
    case Status::Help:
        std::cout << HELP_MESSAGE << std::endl;
        break;
    case Status::NotExistingCommand:
        std::cerr << "'" << argv[1] << "' is not a supported command.\nSee executable_name -h" << std::endl;
        return 1;
    case Status::Encode:
        encode(argv[2], argv[3]);
        break;
    case Status::EncodeWithMeasurement:
        encode(argv[2], argv[3], true);
        break;
    case Status::EncodeHelp:
        std::cout << "executable_name encode <source_file> <output_file>" << std::endl;
        break;
    case Status::EncodeLackOfArgs:
        std::cerr << "Lack of arguments.\nexecutable_name encode <source_file> <output_file>" << std::endl;
        return 2;
    case Status::Decode:
        decode(argv[2], argv[3]);
        break;
    case Status::DecodeWithMeasurement:
        decode(argv[2], argv[3], true);
        break;
    case Status::DecodeHelp:
        std::cout << "executable_name decode <source_file> <output_file>" << std::endl;
        break;
    case Status::DecodeLackOfArgs:
        std::cerr << "Lack of arguments.\nexecutable_name decode <source_file> <output_file>" << std::endl;
        return 3;
    case Status::Analyze:
        analyze_in_dir(argv[2]);
        break;
    case Status::AnalyzeHelp:
        std::cout << "executable_name analyze <source_dir>" << std::endl;
        break;
    case Status::AnalyzeLackOfArgs:
        std::cerr << "Lack of arguments.\nexecutable_name analyze <source_dir>" << std::endl;
        return 4;

    };
    return 0;
}
