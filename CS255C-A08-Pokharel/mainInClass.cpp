#include <iostream>
#include <optional>
#include <variant>
#include <string>

//struct: structure of an object (user-defined)
struct User {
    std::string name;
    int birthyear;
};

//std::optional example
std::optional<User> findBirthYear(int birthyear){
    if(birthyear >= 1980 &&  birthyear <=1990){
        return User{"User" + std::to_string(birthyear), birthyear}; // what is to_string? look up
    }
    return std::nullopt; // if this user is not found
}

//std::variant example
std::variant<int, std::string> getMessage(){
    bool flag = true;

    if (flag){
        return std::string("You found the message");
    } else {
        return 500;
    }
}

//noexcept example
int add(int a, int b) noexcept { // method where you pass in a and b
    return a + b; //it should be guaranteed not ot throw an exception
}

//main to test everything

int main(){

    //test optional with has_value()
    auto user = findBirthYear(1984);

    if(user.has_value()){
        std::cout << "Found user: " << user->name
        << ", Birthyear: " <<user->birthyear << std::endl;
    } else {
        std::cout << "User not found";
    }

    //test variant with std::visit
    auto message = getMessage();
    std::visit([](auto&& value) {
        std::cout << "Message: " << value << "\n";

    }, message);

    //test noexcept
    std::cout << "Add result: " << add(3, 3) << "\n";

    return 0;
};


