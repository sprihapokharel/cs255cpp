#include <iostream>
#include <cstring> //strlen and strcpy functions
#include <utility> // std::move function

class SimpleString {
    private:
        char* buffer;
        size_t length;
    
    public:
        //constructor
        SimpleString(const char* source=""){
            length = std::strlen(source);
            buffer = new char[length+1];
            std::strcpy(buffer, source);
            std::cout << "Created string: " << buffer << std::endl;
        }

        ~SimpleString(){
            delete[] buffer;
            std::cout << "Memory cleared." << std::endl;
        }

        //heavier constructor
        //deep copy
        SimpleString(const SimpleString& inputString) : length(inputString.length){
            buffer = new char[length+1];
            std::strcpy(buffer, inputString.buffer);
            std::cout << "Created string 2: " << buffer << std::endl;
        }

        //manual copy function
        SimpleString& operator=(const SimpleString& other){
            if(this != &other){
                delete[] buffer;
                length = other.length;
                buffer = new char[length + 1];
                std::strcpy(buffer, other.buffer);
            }
            std::cout << "Deep copy of : " << buffer << std::endl;
            return *this;
        }

        //new copy using move function
        SimpleString(SimpleString&& other) noexcept : buffer(other.buffer),
        length(other.length){
            other.buffer = nullptr;
            other.length = 0;
            std::cout << "Stole the buffer!" << std::endl;
        }

        SimpleString& operator=(SimpleString&& other) noexcept {
            if(this!= &other){
                delete[] buffer;
                buffer = other.buffer;
                length = other.length;
                other.buffer = nullptr;
                other.length = 0;
            }
            std::cout << "Move stole the buffer!" << std::endl;
            return *this;
        }

        void print() const {
            if (buffer) std::cout <<  "Content: " << buffer << std::endl;
            else std::cout << "Content is empty." << std::endl;
        }
};

int main() {
    SimpleString a("Hello World");
    SimpleString b = a;
    SimpleString c = std::move(a);

    std::cout << "a: "; a.print();
    std::cout << "b: "; b.print();
    std::cout << "c: "; c.print();
    
    return 0;
}