cmake_minimum_required(VERSION 3.10)

project(ClubSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(ClubSimulation main.cpp solution.cpp)

enable_testing()

add_subdirectory(googletest)

add_executable(runTests g_tests.cpp solution.cpp)

target_link_libraries(runTests gtest gtest_main)

target_include_directories(runTests PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
