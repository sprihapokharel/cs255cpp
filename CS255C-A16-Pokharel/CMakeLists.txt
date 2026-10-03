cmake_minimum_required(VERSION 3.14)
project(CS255C-A16-Pokharel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
)

FetchContent_MakeAvailable(Catch2)

add_library(ThreadSafeBuffer src/ThreadSafeBuffer.cpp)

add_executable(App app/main.cpp)

target_link_libraries(App PRIVATE ThreadSafeBuffer)

target_include_directories(App PRIVATE include)

add_executable(tests tests/tests.cpp)

target_link_libraries(tests PRIVATE ThreadSafeBuffer Catch2::Catch2WithMain)

target_include_directories(tests PRIVATE include)

include(CTest)
include(Catch)

catch_discover_tests(tests)