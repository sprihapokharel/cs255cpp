#include <catch2/catch_test_macros.hpp>
#include "../DataBuffer.h"

// Write 5 test cases for homework

TEST_CASE("Normal operations: adding/summing"){
    DataBuffer db;
    db.add(1);
    db.add(2);
    db.add(3);

    REQUIRE(db.sum() == 6); // writing test cases in the library catch 2. j-unit -> unit testing library for java
}

TEST_CASE("Empty Buffer Sum"){
    DataBuffer db;
    
    REQUIRE(db.sum() == 0);
}

TEST_CASE("Access valid index"){
    DataBuffer db;
    db.add(5);

    REQUIRE(db.get(0).value() == 5);
}