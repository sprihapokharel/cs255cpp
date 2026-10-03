/*

 Practicing how to to Program #2 assigned for homework based on the program (raiiExample/main) written in class.
 Date: 02/01/2026

*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// RAII Class Definition
class ArtAsset { // Creating the class
    public:
        ArtAsset(std::string title) : title(std::move(title)){ // Constructor
            std::cout << "Asset '" << this->title << "' acquired.\n"
        }

        ~ArtAsset(){ // Destructor
            std::cout << "Asset '" << title << "' released.\n";

        }

        void display() const { // Display method to print asset's detials
            std::cout << "Displaying Asset: " << title << "(Format: Digital)\n";
        }

};
