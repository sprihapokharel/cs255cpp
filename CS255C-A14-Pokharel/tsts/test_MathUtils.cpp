/*
Name: Spriha Pokharel
Date: 05/03/2026
Course: CS255C
Assignment: Program #14 - Quality Assurance – Testing & Debugging
*/

#include <catch2/catch_test_macros.hpp>
#include "../MathUtils.h"
#include <stdexcept>

// Writing 5 test cases

// Test Case 1: Normal Operations
TEST_CASE("Normal Operations"){
    MathUtils m;

    REQUIRE(m.factorial(5) == 120);
}

// Test Case 2: Factorial of 0
TEST_CASE("Factorial of Zero"){
    MathUtils m;

    REQUIRE(m.factorial(0) == 1);
}

// Test Case 3: Factorial of 1
TEST_CASE("Factorial of One"){
    MathUtils m;

    REQUIRE(m.factorial(1) == 1);
}

// Test Case 4: Factorial of Negative Number
TEST_CASE("Negative input"){
    MathUtils m;

    REQUIRE_THROWS_AS(m.factorial(-5), std::invalid_argument);
}

// Test Case 5: Normal Operation (higher value)
TEST_CASE("Normal operation with larger value"){
    MathUtils m;

    REQUIRE(m.factorial(12) == 479001600);
}

/*

Debugging Reflection:

The bug I created in MathUtils.cpp was for the recursive case to return n * factorial(n-2). Here, although the code would
have compiled, the output generated for the factorial would be wrong. Test Case 1 and 5 were the test cases which failed (Normal
Operations of finding the factorial of 5 and 10). The remaining test cases were not affected as their implementation in the
source code MathUtils.cpp was still correct and did not have a bug.

After setting a breakpoint for Test Case 1 and monitoring the value of n, n-2, and n == 1 as I stepped through the code, it is
then easy to realize as the value of n changed from 5, to 3, to 1, that the factorial computed was 5*3*1 = 15 (which is not equal to 120).
The values 4 and 2 were skipped over because of the "n-2" logical error.

Unit Testing Reflection:

Unit Testing prevents "regressions" when refactoring code by pointing out the exact test cases it affected as a result. This
allows us to step into the code and identify any logical issues. By defining test cases for the factorial function in MathUtils class,
we are able to clearly outline its intended behavior. If a change in code leads to a difference in behavior as identified from unit testing,
we are able to easily isolate, fix it, and run the tests again.

*/






