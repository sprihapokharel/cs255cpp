/*
Name: Spriha Pokharel
Date: 02/09/2026
Summary: A program to implement a DataBuffer class that manages dynamic memory and demonstrates the Rule of Five, copy, and move 
semantics in order to demonstrate efficient resource management in C++. In the context of this program, when createLargeBuffer() 
returns a DataBuffer, C++ uses move semantics to transfer ownership of the dynamic array instead of copying it which leads to
improvement in efficiency.
External Sources: GeeksforGeeks (https://www.geeksforgeeks.org/cpp/rule-of-five-in-cpp/)
*/

#include <iostream>
#include <utility>

class DataBuffer {
    private:
        int* data;
        size_t size;

    public:
        // Constructor: allocates memory for the array
        DataBuffer(size_t s = 0){
            size = s;
            if(size > 0){
                data = new int[size];
                for(size_t i = 0; i < size; i++){
                    data[i] = i;   // Initialization
                }
            } else {
                data = nullptr;
            }
            std::cout << "Created buffer of size: " << size << std::endl;
        }

        // Destructor: deletes the allocated memory
        ~DataBuffer(){
            delete[] data;
            std::cout << "Memory cleared." << std::endl;
        }

        // Deep copy constructor
        DataBuffer(const DataBuffer& inputBuffer) : size(inputBuffer.size){
            if(size > 0){
                data = new int[size];
                for(size_t i = 0; i < size; i++){
                    data[i] = inputBuffer.data[i];
                }
            } else {
                data = nullptr;
            }
            std::cout << "Created copy of buffer." << std::endl;
        }

        // Deep copy assignment
        DataBuffer& operator=(const DataBuffer& other){
            if(this != &other){
                delete[] data;
                size = other.size;

                if(size > 0){
                    data = new int[size];
                    for(size_t i = 0; i < size; i++){
                        data[i] = other.data[i];
                    }
                } else {
                    data = nullptr;
                }
            }
            std::cout << "Deep copy of buffer." << std::endl;
            return *this;
        }

        // Move constructor
        DataBuffer(DataBuffer&& other) noexcept : data(other.data),
        size(other.size){
            other.data = nullptr;
            other.size = 0;
            std::cout << "Stole the buffer!" << std::endl;
        }

        // Move assignment
        DataBuffer& operator=(DataBuffer&& other) noexcept {
            if(this != &other){
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
            }
            std::cout << "Move stole the buffer!" << std::endl;
            return *this;
        }

        void print() const {
            if(data) std::cout << "Buffer size: " << size << std::endl;
            else std::cout << "Buffer is empty." << std::endl;
        }
};

// Function returning a buffer
DataBuffer createLargeBuffer(){
    DataBuffer temp(10);
    return temp;
}

int main(){
    DataBuffer a(5);
    DataBuffer b = a;
    DataBuffer c = std::move(a);

    std::cout << "a: "; a.print();
    std::cout << "b: "; b.print();
    std::cout << "c: "; c.print();

    DataBuffer d = createLargeBuffer();
    std::cout << "d: "; d.print();

    return 0;
}
