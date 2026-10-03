cmake_minimum_required((VERSION 3.14))
project(CS255C-A14-InClass-Pokharel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
)

FetchContent_MakeAvailable(Catch2)

add_library(DataBuffer.cpp)

add_executable(tests tests/test_DataBuffer.cpp)

target_link_libraries(tests PRIVATE DataBuffer Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)



