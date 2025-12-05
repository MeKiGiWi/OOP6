add_executable(dungeon_test main.cpp)
target_link_libraries(dungeon_test gtest gtest_main livers)
include(GoogleTest)
gtest_discover_tests(dungeon_test)
