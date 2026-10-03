/*

Name: Spriha Pokharel
Date: 03/24/2026
Assignment 09
Summary: Writing generic programming solutions using Function and Class Templates (which handle multiple data types) while
        using concepts to provide clear constraints on what types the templates can accept.
Sources: https://gkteco.medium.com/using-c-concepts-for-great-good-part-1-2ae42c7a0d6d

*/

#include <iostream>
#include <string>
#include <concepts>

// Constrained Function Template
template <std::totally_ordered T> T findMax(T a, T b){
    if (a > b){
        return a;
    } else {
        return b;
    }  
};

// Generic Class Template
template <typename T>
class Holder {
    private:
        T value;
    public:

    // Constructor
    Holder (T v) {
        value = v;
    }

    // Getter
    T getValue(){
        return value;
    }

    void show(){
        std::cout << "Value: " << value << std::endl;
    }
};

// Specific method to print unique message if T is a std::string
template<> void Holder<std::string>::show(){
    std::cout << "This datatype was a string: " << value << std::endl;
}

// Modern Template Concepts
template <typename T> concept SimpleNumber = requires(T x){
    x + x;
    x - x;
};

// Function calculateDouble(T value) that returns value + value (double the value passed)
template <SimpleNumber T> T doubleVal(T x){
    return x + x;
};

int main(){

    // Testing the findMax function
    std::cout << "The maximum numeric value is: " << findMax(3, 6) << std::endl;
    std::cout << "The maximum string value is: " << findMax("apple", "pineapple") << std::endl;

    // Testing the class template
    Holder<int> holder1(8);
    holder1.show();

    Holder<std::string> holder2("I love CPP!");
    holder2.show();

    // Testing the concept function
    std::cout << "The double of value passed in is: " << doubleVal(6) << std::endl;
    // std::cout << "The double of value passed in is: " << doubleVal("hello") << std::endl;

    /*
    Using Concepts provides better error messages than standard templates because the compiler checks constraints early in template instantiation. If a type does not satisfy the required Concept,
    the error is reported at the call site with a clear explanation of which constraint failed. This avoids the long and complex error messages that often result from deep template instantiation.
    */
    return 0;
}

