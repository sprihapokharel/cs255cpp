#include <iostream>
#include <vector>
#include <string>
#include <memory>

//RAII Class Definition
class MusicTrack {
    public: // methods and functions
        MusicTrack(std::string title) : title(std::move(title)){
            std::cout << "[Acquisition] Track '" << this->title << "' acquired.\n"; // syntax for making a constructor in C++
        }

        ~MusicTrack(){
            std::cout << "[Release] Track '" << title << "' released.\n";

        }

        void display() const {
            std::cout << "Displaying Track: " << title << "(Format: Digital)\n";
        }


    private: // variable declarations
        std::string title;
};

// Some ownership functions: smart-pointers. Unique or shared ownership pointers.

void processTrack(std::unique_ptr<MusicTrack> track){
    std::cout << ">> Function 'processTrack' now owns the unique pointer. \n";
    track->display();

    // destructor will be called when track is out of scope (~), memory management.
    // it will automatically clean up the pointer in this object when we're done with it.

}

// making another function

void uniquePointerRun() {
    std::cout << "\n---Test Run of Unique---\n";

    auto trackA = std::make_unique<MusicTrack>("Symphony No.20"); // auto tells it it'll be a music track type

    std::cout << "Moving trackA to processTrack\n";

    processTrack(std::move(trackA));

    if(trackA == nullptr){
        std::cout << "TrackA is null after the move.\n";
    }

}

// doing the same thing but with shared pointer

void sharedPointerRun(){
    std::cout << "\n---Test Run of Shread\n";
    std::shared_ptr<MusicTrack> sharedTrack = std::make_shared<MusicTrack>("New Music No. 5");
    std::cout << "Count (1 owner): " << sharedTrack.use_count() << "\n";
    {
        std::cout << "Entering inner scope \n";
        std::shared_ptr<MusicTrack> observer1 = sharedTrack;
        std::cout << "Count (2 owner): " << sharedTrack.use_count() << "\n";

        {
        
            std::shared_ptr<MusicTrack> observer2 = sharedTrack;
            std::cout << "Count (3 owner): " << sharedTrack.use_count() << "\n";

        } // observer 2 should be destroyed here
        std::cout << "Count (back to 2)): " << sharedTrack.use_count() << "\n";
        std::cout << "Count (back to 1): " << sharedTrack.use_count() << "\n";
        std::cout << "Resetting the final pointer \n";
        sharedTrack.reset(); // destructor called here
        std::cout << "share completed \n";


    }

    int main(){
        uniquePointerRun();
        sharedPointerRun();

        std::cout << "Finished program \n";
        return 0;
    }

