#include <iostream>
#include <vector>

int main(){
    std::vector<int> numbers(5);

    int counter = 10;

    for(auto& element : numbers){
        element = counter;
        counter += 10;
    }

    std::cout << "Vector elements: ";
    for(const auto element : numbers){
        std::cout << element << " ";
    }
    return 0;
}