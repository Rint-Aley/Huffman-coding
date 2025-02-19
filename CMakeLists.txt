cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(huffman_coding)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(huffman_coding
 "src/main.cpp"
 "src/cli.cpp"
 "src/encode.cpp"
 "src/measurement.cpp"
 "src/BitWriter.cpp"
 "src/HuffmanTree.cpp"
 "src/decode.cpp"
 "src/BitReader.cpp"
)

enable_testing()

add_executable(
 tests
 "tests/cli_test.cpp"
 "tests/huffman_tree_test.cpp"
 "tests/bit_writer_test.cpp"
 "tests/tree_writing_test.cpp"
 "tests/tree_reading_test.cpp"
 "src/cli.cpp"
 "src/encode.cpp"
 "src/decode.cpp"
 "src/measurement.cpp"
 "src/HuffmanTree.cpp"
 "src/BitWriter.cpp"
 "src/BitReader.cpp"
)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)