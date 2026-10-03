/*

Name: Spriha Pokharel
Date: 02/19/2026
Summary: A program that performs a series of transformations on a vector containing 20 random integers (with range 1-100)
        without the use of a manual for loop.
External Sources: GeeksforGeeks (https://www.geeksforgeeks.org/cpp/iterators-c-stl/), (https://www.geeksforgeeks.org/cpp/stddistance-in-c/),
                                (https://www.geeksforgeeks.org/cpp/std-find-in-cpp/).

*/

#include <iostream>
#include <vector>
#include <algorithm> // allows modification for ranges of data from data structures (searching, sorting, counting, comparing)
#include <iterator>
#include <string>
#include <random>

int main(){
    std::random_device rd; // an instance of the std::random device class, used to generate a random seed value
    std::mt19937 gen(rd()); // pseudo-random gen(erator) that implements the mersenne twister algorithm, seed value is passed to the gen constructor (determines the starting value of the random generator)
    std::uniform_int_distribution<> dis(1, 100); // distribution object dis: creates values between 1-100 inclusive (each has equal probability)
    std::vector<int> numbers (20); // container to hold the 20 int values, value initialized to 0 at first, dynamic (grow/shrink during runtime) bc vector manages dynamic heap storage internally

    // Filing the numbers vector with values obtained from the Lamda Function
    std::generate(numbers.begin(), numbers.end(), [&]() {
        return dis(gen);
    });

    // Sorting in descending order
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());

    // Moving all even numbers to the front of the vector
    std::partition(numbers.begin(), numbers.end(), [](int n){
        return n % 2 == 0;
    });

    // Printing the vector with Lamda
    std::cout << "Vector: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n){
        std::cout << n << " ";
    });
    std::cout << "\n";

    // Creating a new vector of strings called 'results'
    std::vector<std::string> results;

    // Iterating through numbers vector & storing 'HIGH' if >50 or 'LOW' if <50 in 'results'
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(results), [](int n){
        return (n > 50) ? "HIGH" : "LOW";
    });

    // Displaying results
    std::cout << "High/Low Results: ";
    for(const auto& s : results) std::cout << s << " ";
    std::cout << "\n";

    // Locating number 50 or closest to it
    auto it = std::find(numbers.begin(), numbers.end(), 50);

    if (it != numbers.end()) {
        std::cout << "Distance of 50 from beginning: " << std::distance (numbers.begin(), it) << "\n";
    }
    else {
        auto closest = std::min_element(numbers.begin(), numbers.end(),[](int a, int b) {
            return std::abs(a - 50) < std::abs(b - 50);
        });
    std::cout << "Closest value to 50: " << *closest << "\n";
    std::cout << "Distance from beginning: " << std::distance(numbers.begin(), closest) << "\n";
    }

    return 0;
}

/*
Part 3 Reflection:

We use v.begin() and v.end() instead of passing the vector itself into these algorithms because they return iterators where
v.begin() points to the beginning whereas v.end() points to one position after the end. By using these iterators, we can make use
of the STL Algorithm on different container types beyond vectors. Furthermore, it helps us specify exactly the range of data within
the container that we want to work on instead of passing the entire container in and having to make changes to it all.

*/