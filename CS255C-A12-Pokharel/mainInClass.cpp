#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

// load from DB fake function
std::vector<int> loadFromDB(){
    std::this_thread::sleep_for(std::chrono::seconds(2)); // vec function will sleep for 2 seconds and return the vec
    return {10, 20, 30, 40, 50}; // can be anything, 3, 4, 6, 8
}

// worker function to send message back
void backgroundTask(std::promise<std::string> & msgPromise){ // & = reference variable
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string result = "Finished Retrieving Data!";
    msgPromise.set_value(result);
}


// test driver
int main (){

    // async task
    std::future<std::vector<int>> futureData = 
        std::async(std::launch::async, loadFromDB);

    // responsiveness
    while(futureData.wait_for(std::chrono::milliseconds(200)) !=
        std::future_status::ready){
            std::cout << "Loading...\n";
        }

        std::vector<int> data = futureData.get();

        std::cout << "Data received: ";
        for(int num : data){
            std::cout << num << " ";
        }

    // future/promise
    std::promise<std::string> messagePromise;
    std::future<std::string> messageFuture = messagePromise.get_future();

    std::thread worker(backgroundTask, std::ref(messagePromise));
    
    std::cout << "Waiting for worker...\n";
    std::string message = messageFuture.get();
    std::cout << "Message: " << message << std::endl;

    worker.join(); // concept of branching and coming back to the main thread (application/idea in bitbucket, github, etc; being in main, branching off, testing, & then coming back)

    // execution policies

    return 0;
}

