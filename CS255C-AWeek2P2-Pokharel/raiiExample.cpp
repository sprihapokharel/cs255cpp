#include <iostream>
#include <vector>
#include <string>
#include <memory>

// RAII class definition
class MusicTrack {
    public:
        MusicTrack(std::string title) : title(std::move(title)){
            std::cout << "[Acquisition] Track '" << this->title << "' acquired.\n";
        }

        ~MusicTrack(){
            std::cout << "[Release] Track '" << title << "' released.\n";
        }

        void display() const {
            std::cout << "Displaying Track: " << title << "(Format: Digital)\n";
        }

    private:
        std::string title;
};

void processTrack(std::unique_ptr<MusicTrack> track){
    std::cout << ">> Function 'processTrack' now owns the unique pointer. \n";
    track->display();
    //destructor will be called when track is out of scope
}

void uniquePointerRun() {
    std::cout << "\n---Test Run of Unique---\n";
    
    auto trackA = std::make_unique<MusicTrack>("Symphony No.20");
    
    std::cout << "Moving trackA to processTrack\n";

    processTrack(std::move(trackA));

    if(trackA == nullptr){
        std::cout << "TrackA is null after the move.\n";
    }
}

void sharedPointerRun(){
    std::cout << "\n---Test Run of Shared\n";
    std::shared_ptr<MusicTrack> sharedTrack = std::make_shared<MusicTrack>("New Music No. 5");
    std::cout << "Count (1 owner): " << sharedTrack.use_count() << "\n";

    {
        std::cout << "Entering inner scope \n";
        std::shared_ptr<MusicTrack> observer1 = sharedTrack;
        std::cout << "Count (2 owner): " << sharedTrack.use_count() << "\n"; 
        {
            std::shared_ptr<MusicTrack> observer2 = sharedTrack;
            std::cout << "Count (3 owner): " << sharedTrack.use_count() << "\n"; 
        } //observer 2 should be destroyed here

        std::cout << "Count (back to 2): " << sharedTrack.use_count() << "\n";
    }
    std::cout << "Count (back to 1): " << sharedTrack.use_count() << "\n";
    std::cout << "Resetting the final pointer \n";
    sharedTrack.reset(); // destructor called here
    std::cout << "shared completed \n";
}

int main(){
    uniquePointerRun();
    sharedPointerRun();

    std::cout << "Finished program \n";
    return 0;
}