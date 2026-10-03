#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

int main() {
    std::cout << "ßBasic Lambda\n";
    auto hello = []() {
        std::cout << "Hello from a lambda!\n";
    };
    hello();

    std::cout << "\nLambda with Parameters\n";
    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << "3 + 4 = " << add(3, 4) << "\n";

    std::cout << "\nCapturing Variables\n";
    int x = 10;

    auto by_value = [x]() {
        std::cout << "Captured by value: " << x << "\n";
    };

    auto by_reference = [&x]() {
        x += 5;
    };

    by_value();
    by_reference();
    std::cout << "After reference capture, x = " << x << "\n";

    std::cout << "\nMutable Lambda\n";
    auto counter = [count = 0]() mutable {
        return ++count;
    };

    std::cout << counter() << "\n";
    std::cout << counter() << "\n";

    std::cout << "\nLambdas with STL Algorithms\n";
    std::vector<int> numbers{1, 2, 3, 4, 5};

    std::cout << "Original: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    std::sort(numbers.begin(), numbers.end(),
              [](int a, int b) {
                  return a > b; // descending
              });

    std::cout << "Sorted descending: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0,
                              [](int total, int value) {
                                  return total + value;
                              });

    std::cout << "Sum = " << sum << "\n";

    std::cout << "\nGeneric Lambda (C++14+)\n";
    auto multiply = [](auto a, auto b) {
        return a * b;
    };

    std::cout << "2 * 3 = " << multiply(2, 3) << "\n";
    std::cout << "2.5 * 4.0 = " << multiply(2.5, 4.0) << "\n";

    std::cout << "\nconstexpr Lambda\n";
    constexpr auto square = [](int n) {
        return n * n;
    };

    static_assert(square(5) == 25);
    std::cout << "Square of 6 = " << square(6) << "\n";

    std::cout << "\nRecursive Lambda (C++23)\n";
    auto factorial = [](this auto self, int n) -> int {
        if (n <= 1) return 1;
        return n * self(n - 1);
    };

    std::cout << "Factorial of 5 = " << factorial(5) << "\n";

    std::cout << "\nLambda as Callback\n";
    auto run_twice = [](auto func) {
        func();
        func();
    };

    run_twice([]() {
        std::cout << "Running callback!\n";
    });

    std::cout << "\nProgram Finished\n";
    return 0;
}