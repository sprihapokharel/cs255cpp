/*
Name: Spriha Pokharel
Date: 03/09/2026
Summary: A program that implements a simple command pattern using a std::vector of std::function<void(double&)> objects, storing different callable types (a lambda, a regular function, and a bound function) 
and executing them with an STL algorithm.

Sources:

- https://en.cppreference.com/w/cpp/utility/functional/function.html
- https://www.geeksforgeeks.org/cpp/std-function-in-cpp/
- https://stackoverflow.com/questions/25848690/should-i-use-stdfunction-or-a-function-pointer-in-c

*/



#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath> // for std::pow

// global functions

// regular function
void addTen(double& value){
    value += 10;
}

// bind function
void power(double& base, int exp){
    base = std::pow(base, exp); // raise base to exponent
}

int main(){

    // command registry
    std::vector<std::function<void(double&)>> commands;

    // register different callables

    // lambda function
    commands.push_back([](double& val){
        val *= 5;
    });

    // regular function
    commands.push_back(addTen);

    // bound function using std::bind
    using namespace std::placeholders;
    commands.push_back(std::bind(power, _1, 2));

    // data variable passed into the commands
    double myData = 5.0;

    // execute all stored commands on myData
    std::for_each(commands.begin(), commands.end(),
        [&](std::function<void(double&)>& cmd){
            cmd(myData);
        });

    // print final result
    std::cout << "Final result: " << myData << std::endl;

    return 0;
}

// lambda: 5 * 5 = 25
// addTen: 25 + 10 = 35
// power ^2: 35^2 = 1225

/*
Why is std::function more flexible than traditional function pointer?

std::function can store many different callable types that share the same
function signature. In this program, the vector "commands" stores a lambda,
a regular function (addTen), and a bound function created with std::bind.
A traditional function pointer could only store regular functions, but
std::function allows us to treat all these different callable objects as
the same type and store them in one container.

*/