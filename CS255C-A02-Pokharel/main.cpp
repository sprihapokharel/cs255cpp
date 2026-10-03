/*
    Name: Spriha Pokharel
    Date: 02/01/2026
    Summary: A system to manage the "ArtAsset" objects by implementing the RAII pattern.
    External Sources: GeeksforGeeks (https://www.geeksforgeeks.org/cpp/smart-pointers-cpp/)

    Reflection:
    std::unique_ptr is preferred over std::shared_ptr as a default choice because std::unique_ptr has sole
    ownership which allows it to own a resource by itself. It has less overhead than std::shared_ptr as it uses as much
    memory as a raw pointer and implementation of RAII, this allows the resource to be automatically cleaned up when it
    goes out of scope. 
    
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

// Creating the ArtAsset Class
class ArtAsset {
public:
    // Constructor
    ArtAsset(std::string title, int fileSizeMB) 
        : title(std::move(title)), fileSizeMB(fileSizeMB) {
        std::cout << "Asset " << this->title << " acquired.\n";
    }

    // Destructor
    ~ArtAsset() {
        std::cout << "Asset " << title << " released.\n";
    }

    // Method to display details
    void display() const {
        std::cout << "Displaying Asset: " << title << " (" << fileSizeMB << "MB)\n";
    }

private:
    std::string title;
    int fileSizeMB;
};p

// Function to demonstrate transferring unique ownership

void processAsset(std::unique_ptr<ArtAsset> asset) {
    // Function 'processAsset' now owns the pointer
    if (asset) {
        asset->display();
    }
    // Destructor is called automatically here as 'asset' goes out of scope
}

int main() {
    std::cout << "\n--- Unique Ownership ---\n";

    // Creating a unique_ptr using std::make_unique
    std::unique_ptr<ArtAsset> uniquePtr = std::make_unique<ArtAsset>("The Last Supper", 50);

    // unique_ptr is move-only so you cannot copy this pointer (if you do, it will lead to an error)
    
    // Using std::move() to transfer ownership
    processAsset(std::move(uniquePtr));

    // Observing behavior after move
    if (uniquePtr == nullptr) {
        std::cout << "uniquePtr is now null in main() because ownership was moved.\n";
    }
    // The destructor for "The Last Supper" is called inside processAsset

    std::cout << "\n--- Shared Ownership ---\n";

    // Creating a shared_ptr for different artwork
    std::shared_ptr<ArtAsset> sharedPtr1 = std::make_shared<ArtAsset>("Mona Lisa", 35);
    std::cout << "Created sharedPtr1. Use Count: " << sharedPtr1.use_count() << "\n";

    {
        // Creating a second shared_ptr instance that points to the same asset
        std::shared_ptr<ArtAsset> sharedPtr2 = sharedPtr1;
        std::cout << "Created sharedPtr2. Use Count: " << sharedPtr1.use_count() << "\n";

        // Creating a third shared_ptr instance that points to the same asset
        std::shared_ptr<ArtAsset> sharedPtr3 = sharedPtr1;
        std::cout << "Created sharedPtr3. Use Count: " << sharedPtr1.use_count() << "\n";

        // Resetting the pointers
        sharedPtr3.reset();
        std::cout << "sharedPtr3 reset. Use Count: " << sharedPtr1.use_count() << "\n";

        std::cout << "sharedPtr2 going out of scope now...\n"; // sharedPtr2 goes out of scope here
    } 

    std::cout << "Back in main scope. Use Count: " << sharedPtr1.use_count() << "\n";

    std::cout << "Resetting sharedPtr1 (last owner)...\n";
    sharedPtr1.reset();
    std::cout << "sharedPtr1 reset.\n";

    std::cout << "\nFinished program.\n";
    return 0;
}