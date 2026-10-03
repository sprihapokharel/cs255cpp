/*

Name: Spriha Pokharel
Date: 03/23/2026
Assignment: 08
Summary: A program that implements error signaling using std::optional, std::variant, and noexcept.

*/

#include <iostream>
#include <optional>
#include <variant>
#include <string>

// Creating a struct User with name & age
struct User {
    std::string name;
    int age;
};

// Function to findUser(int id) that returns an std::optional<User>
std::optional<User> findUser(int id){
    if (id>=1 && id<=5){
        return User{"User" + std::to_string(id), id};
    }
    return std::nullopt;
}

// Function to getDatabaseStatus() that returns a std::variant<int, std::string>
std::variant<int, std::string> getDatabaseStatus(){
    bool flag = true;

    if (flag){
        return 314;
    } else{
        return std::string("System is healthy!");
    }
}

int multiply (int a, int b) noexcept {
    return a * b;
}

int main() {

    // Testing std::optional
    auto user = findUser(2);

    if (user.has_value()){
        std::cout << "Found user: " << user->name
        << ", Age: " <<user->age << std::endl;
    } else {
        std::cout << "User not found";
    }

    // Testing std::variant
    auto status = getDatabaseStatus();
    std::visit([](auto&& value) {
        std::cout << "Database status: " << value << "\n";
    }, status);

    // Testing noexcept
    std::cout << "Multiply result: " << multiply(2, 4) << "\n";
    
    return 0;

};

/*

Reflection: Explain the difference between using an exception and using std::optional for
            a function that simply fails to find a value.

            std::optional is typically used in situations where the potential error invoked is non-fatal like a failed returned error. This is especially
            useful to us in situations like above where there is no guarantee whether or not we will find a user, but in the case that the
            user is not found (value may or may not be returned), we want the program to simply check for its presence without using exceptions or causing
            the entire program to crash, thus making it "optional". However, exceptions are still extremely important and useful to us in cases when the system 
            may face unexpected or fatal errors, but may not be the most efficient to use for a function that simply fails to find a value.

            Note: I was also unable to compile this program regularly so I looked it up and was told to run the following through the terminal and explicitly
            declare version 20, after which it started to work:

            g++ -std=c++20 main.cpp -o main

*/