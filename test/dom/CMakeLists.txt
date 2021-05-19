cmake_minimum_required(VERSION 3.20.1)

add_executable(ElementTests ElementTests.cpp)
add_executable(NodeTests NodeTests.cpp)
add_executable(TextTests TextTests.cpp)

target_link_libraries(ElementTests PUBLIC
    gtest_main
    src_dom
)

target_link_libraries(NodeTests PUBLIC
    gtest_main
    src_dom
)

target_link_libraries(TextTests PUBLIC
    gtest_main
    src_dom
)

add_test(
    NAME ElementTests
    COMMAND ElementTests
)

add_test(
    NAME NodeTests
    COMMAND NodeTests
)

add_test(
    NAME TextTests
    COMMAND TextTests
)