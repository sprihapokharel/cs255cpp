#include <iostream>
#include <string>

struct student {
    std::string name;
    int age;
    char grade;
};

int main(){

student student1;
student1.name = "Spriha";
student1.age = 19;
student1.grade = 'A';

std::cout << student1.name << std::endl;
std::cout << student1.age << std::endl;
std::cout << student1.grade << std::endl;

return 0;

};
