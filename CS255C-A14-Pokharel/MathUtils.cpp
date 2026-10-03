#include "MathUtils.h"
#include <stdexcept>

int MathUtils::factorial(int n) const {
    if (n < 0) {
        throw std::invalid_argument("Factorial is undefined for negative numbers");
    }

    // base case
    if (n == 0 || n == 1) {
        return 1;
    }

    // recursive case
    return n * factorial(n - 1); // introducing a bug here as factorial(n - 2)
}