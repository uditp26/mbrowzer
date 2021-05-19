cmake_minimum_required(VERSION 3.20.1)

add_executable(ParserTests ParserTests.cpp)

target_link_libraries(ParserTests PUBLIC
    gtest_main
    src_html
    src_dom
)

add_test(
    NAME ParserTests
    COMMAND ParserTests
)