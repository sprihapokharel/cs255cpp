#include <iostream>
#include <string>
#include <concepts>

//constrained function template
template <std::totally_ordered T> T maxValue(T a, T b){ // passing in generic type T a or T b (could be 1, and 2), App and Apple (longer so greater), etc. Want to return which one is bigger.
    if (a > b){
        return a;
    } else {
        return b;
    }
};

//generic class template
template <typename T>
class Holder {
    private:
        T value;
    public:

    //constructor
    Holder(T v) {
        value = v;
    }

    //getter
    T getValue(){
        return value;
    }

    void show(){ //printing out the value regardless of what its data type is
        std::cout << "Value: " << value << std::endl;
    }

};

//outside of the class, we'll do
//pretty print for string
template<> void Holder<std::string>::show(){ // overwriting the show method when the datatype is string (to pretty print instead of what's above)
    std::cout << "This datatype was a string: " << value << std::endl;
}

//custom concepts
//checks to see if add and subtract can be done
template <typename T> concept SimpleNumber = requires(T x) { // looks similar to the lambda function
    x + x;
    x - x;
};

//doubleval, but writing as
//triple the number (write doubleVal and do x + x instead)
template <SimpleNumber T> T tripleVal(T x){
    return x + x + x;
};

int main (){
    
    //test the max function
    std::cout << maxValue(4, 8) << std::endl;
    std::cout << maxValue(std::string("cat"), std::string("dog")) <<std::endl;

    //test the class
    Holder<int> holder1(5); //while testing, must specify the value (int, string, etc.)
    holder1.show();

    Holder<std::string> holder2("hello"); //writing this to invoke the other print method
    holder2.show();

    //test the concept function
    std::cout <<tripleVal(3) << std::endl; //expecting 9 to be printed out

    return 0;
}