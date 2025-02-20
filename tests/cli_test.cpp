#include <gtest/gtest.h>
#include "../src/cli.h"

TEST(CLI, Help) {
	const char* args[]{ "source", "-h", "something other" };
	int argc = 2;
	ASSERT_EQ(Status::Help, parse_args(argc, args));
	argc = 3;
	ASSERT_EQ(Status::Help, parse_args(argc, args));

	args[1] = "--help";
	argc = 2;
	ASSERT_EQ(Status::Help, parse_args(argc, args));
	argc = 3;
	ASSERT_EQ(Status::Help, parse_args(argc, args));
}

TEST(CLI, Decode) {
	const char* args[]{ "source", "decode", "file1", "file2", "--measure", "something other"};
	int argc = 4;
	ASSERT_EQ(Status::Decode, parse_args(argc, args));

	argc = 6;
	ASSERT_EQ(Status::DecodeWithMeasurement, parse_args(argc, args));
	argc = 5;
	ASSERT_EQ(Status::DecodeWithMeasurement, parse_args(argc, args));

	args[4] = args[5];
	ASSERT_EQ(Status::Decode, parse_args(argc, args));

	argc = 3;
	ASSERT_EQ(Status::DecodeLackOfArgs, parse_args(argc, args));

	args[2] = "-h";
	argc = 3;
	ASSERT_EQ(Status::DecodeHelp, parse_args(argc, args));
	argc = 4;
	ASSERT_EQ(Status::DecodeHelp, parse_args(argc, args));

	args[2] = "--help";
	argc = 3;
	ASSERT_EQ(Status::DecodeHelp, parse_args(argc, args));
	argc = 4;
	ASSERT_EQ(Status::DecodeHelp, parse_args(argc, args));
}

TEST(CLI, Encode) {
	const char* args[]{ "source", "encode", "file1", "file2", "--measure", "something other" };
	int argc = 4;
	ASSERT_EQ(Status::Encode, parse_args(argc, args));

	argc = 6;
	ASSERT_EQ(Status::EncodeWithMeasurement, parse_args(argc, args));
	argc = 5;
	ASSERT_EQ(Status::EncodeWithMeasurement, parse_args(argc, args));

	args[4] = args[5];
	ASSERT_EQ(Status::Encode, parse_args(argc, args));

	argc = 3;
	ASSERT_EQ(Status::EncodeLackOfArgs, parse_args(argc, args));

	args[2] = "-h";
	argc = 3;
	ASSERT_EQ(Status::EncodeHelp, parse_args(argc, args));
	argc = 4;
	ASSERT_EQ(Status::EncodeHelp, parse_args(argc, args));

	args[2] = "--help";
	argc = 3;
	ASSERT_EQ(Status::EncodeHelp, parse_args(argc, args));
	argc = 4;
	ASSERT_EQ(Status::EncodeHelp, parse_args(argc, args));
}
TEST(CLI, Analyze) {
    const char* args[]{ "source", "analyze", "directory", "something other" };
    int argc = 3;
    ASSERT_EQ(Status::Analyze, parse_args(argc, args));

    argc = 4;
    ASSERT_EQ(Status::Analyze, parse_args(argc, args));

    argc = 2;
    ASSERT_EQ(Status::AnalyzeLackOfArgs, parse_args(argc, args));

    args[2] = "-h";
    argc = 3;
    ASSERT_EQ(Status::AnalyzeHelp, parse_args(argc, args));
    argc = 4;
    ASSERT_EQ(Status::AnalyzeHelp, parse_args(argc, args));

    args[2] = "--help";
    argc = 3;
    ASSERT_EQ(Status::AnalyzeHelp, parse_args(argc, args));
    argc = 4;
    ASSERT_EQ(Status::AnalyzeHelp, parse_args(argc, args));
}

TEST(CLI, NotExistingCommand) {
	const char* args[]{ "source", "1", "2"};
	int argc = 3;
	ASSERT_EQ(Status::NotExistingCommand, parse_args(argc, args));

	argc = 1;
	ASSERT_EQ(Status::NoArgs, parse_args(argc, args));
}