/*  Name: Spriha Pokharel
    Date: 01/25/2026
    Summary: A simple command-line application that manages a list of student 
    names and their expected graduation years.
    External Sources: GeeksforGeeks (https://www.geeksforgeeks.org/cpp/range-based-loop-c/ and https://www.geeksforgeeks.org/cpp/vector-of-strings-in-cpp/) 
*/

#include <iostream>
#include <vector>
#include <string>

int main(){
    std::vector<std::string> names{"Spriha", "Mia", "Tenzin", "Riley", "Emma"}; // declaring a vector of strings with names
    std::vector<int>grad_years{}; // creating a second vector for graduation years

    int grad_year; // creating input variable (int) for grad year

    for (auto name:names) { // iterate through the names vector
        std::cout << "Enter " << name << "'s graduation year: "; // prompt user for grad year
        std::cin >> grad_year;
        grad_years.push_back(grad_year); // add each grad year into grad_years vector
    }

    std::cout << "\nClass Roster:\n";

    for (int i = 0; i < names.size(); i++) { // print a simple formatted output of names & grad year
        std::cout << "\nStudent: " << names[i] << " | Class of: " << grad_years[i] << "\n" << std::endl;
    }
}