#ifndef CLI_H_
#define CLI_H_
enum Status {
	NoArgs,
	Help,
	Encode,
	Decode,
	Analyze,
	EncodeHelp,
	DecodeHelp,
	AnalyzeHelp,
	EncodeLackOfArgs,
	DecodeLackOfArgs,
	AnalyzeLackOfArgs,
	NotExistingCommand,
	EncodeWithMeasurement,
	DecodeWithMeasurement,
};

Status parse_args(int argc, const char* argv[]);
#endif