#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <random>

int main(){
    // getting the random 1-100, setting up this random object to go from 1-100, we'll call it when we're ready to
    // populate our vector
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // vector of random 1 through 100
    std::vector<int> numbers(20);

    // generate function to intialize the vector, and populate it using the distribution of 1-100 randomly
    // w/o us having to loop through the vector: basically like a "for loop in one line"

    // create and initialize a vector of random 1 - 100
    std::generate(numbers.begin(), numbers.end(), [&]() { // generate random numbers [&] and put in random distribution, could have duplicates
        return dis(gen);
    });

    // sort/filter (not passing the vector itself, we're passing in the beginning & end of the vector)
    // descending sort -> determined by the greater function
    std::sort(numbers.begin(), numbers.end(), std::greater<int>()); // (first element, last element, how you want to sort it)

    // evens
    std::partition(numbers.begin(), numbers.end(), [](int n){
        return n % 2 == 0;
    });

    // printing the vector only using an iterator
    std::cout << "Vector: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n){
        std::cout << n << " ";
    });
    std::cout << "\n";

    // high/low based on less than 50
    std::vector<std::string> results;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(results), [](int n){
        return (n > 50) ? "HIGH" : "LOW"; // is it greater than 50? if then -> high, else -> low
    });

    // printing high/low results
    std::cout << "High/Low Results: ";
    for(const auto& s : results) std::cout << s << " ";
    std::cout << "\n";

    return 0;

    // introducing the short way of doing things (instead of lengthy if-else statements), what is the latest use in the tech
    // world / in industry

    // so far, parts 1 and 2 of the assignment 5 complete. on your own: finish part 3.
}
