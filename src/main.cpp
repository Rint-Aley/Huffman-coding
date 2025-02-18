#include <iostream>
#include "cli.h"
#include "encode.h"

int main(int argc, char** argv) {
    const char* HELP_MESSAGE = "executable_name [-h] [--help] - shows this message\n"
        "executable_name encode <source_file> <output_file> - encodes source file and writes it in output file\n"
        "executable_name decode <source_file> <output_file> - decodes encrypted source file and writes it in output file";
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
        //TODO: call decode
        break;
    case Status::DecodeWithMeasurement:
        //TODO: call decode
        break;
    case Status::DecodeHelp:
        std::cout << "executable_name decode <source_file> <output_file>" << std::endl;
        break;
    case Status::DecodeLackOfArgs:
        std::cerr << "Lack of arguments.\nexecutable_name decode <source_file> <output_file>" << std::endl;
        return 3;
    };
    return 0;
}
