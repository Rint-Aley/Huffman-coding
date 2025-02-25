#ifndef CLI_H_
#define CLI_H_
enum Status {
	NoArgs,
	Help,
	Encode,
	Decode,
	EncodeHelp,
	DecodeHelp,
	EncodeLackOfArgs,
	DecodeLackOfArgs,
	NotExistingCommand,
	EncodeWithMeasurement,
	DecodeWithMeasurement,
};

Status parse_args(int argc, const char* argv[]);
#endif