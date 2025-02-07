#include "cli.h"
#include <cstring>

Status parse_args(int argc, char *argv[]) {
    if (argc == 1)
        return Status::NoArgs;
    if (argc > 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")))
        return Status::Help;
    if (!strcmp(argv[1], "encode")) {
        if (argc > 2 && (!strcmp(argv[2], "-h") || !strcmp(argv[2], "--help")))
            return Status::EncodeHelp;
        if (argc >= 4)
            return Status::Encode;
        else
            return Status::EncodeLackOfArgs;
    }
    if (!strcmp(argv[1], "decode")) {
        if (argc > 2 && (!strcmp(argv[2], "-h") || !strcmp(argv[2], "--help")))
            return Status::DecodeHelp;
        if (argc >= 4)
            return Status::Decode;
        else
            return Status::DecodeLackOfArgs;
    }
    return Status::NotExistingCommand;
}

