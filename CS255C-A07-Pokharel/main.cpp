#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath> // for the exponent

// global functions
// exist outside of main/global scope of program

// regular
void addFive(double& value){ // add 10 in hw
    value += 5;
    // value = value + 5;
}

// bind function
void power(double& base, int exp){ // of void return type also
    base = std::pow (base, exp); // coming from <cmath> on top
}

// can't say base = 5, base is internal to that function/variable
// but power is global, can call it from anywhere in the code


int main(){

    // command registry
    std::vector<std::function<void(double&)>>commands; // making a vector called commands that doesn't have anything in it

    // register different callables (such as lambda,
    // regular function, and bind function)

    // lambda: has a capture, then our variables
    commands.push_back([](double& val){ // function on a vector
        val *= 3; // you get to define this value

    });

    commands.push_back(addFive); // just calling the function above

    // switch namespaces from std to placeholders
    using namespace std::placeholders;
    // bind function
    commands.push_back(std::bind(power, _1, 2)); // look up bind; just calling the function above

    // execution of the commands now
    // data variable to pass in to the commands
    double myData = 5.0; // can ask user for a value here

    // loop through commands vector to call each function
    // passing in myData
    std::for_each(commands.begin(), commands.end(), // diff between calling functions earlier to calling it here through the lambda
        [&](std::function<void(double&)>&cmd){
            cmd(myData);
        });

    // print the results
    std::cout << "Final results: " << myData << std::endl; // can do endl or just '\n'

    // need to be modified a little to meet prog #8 requirements

    return 0;

    // 5 * 3 = 15, + 5 = 20
    // power of 20 ^ 2 = 400

}