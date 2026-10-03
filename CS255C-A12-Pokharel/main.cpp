/*
Name: Spriha Pokharel
Date: 04/19/2026
Class: CS255C
Assignment 12: Concurrency 3 - Futures & Promises
Summary: Simulating an application that fetches data from a slow external source (database/ Web API) without
blocking the main user interface, experimenting with std::launch::async and std::launch::deferred.
*/

#include <iostream>
#include <vector>
#include <thread>
#include <future> // what will allow us to use async
#include <chrono>

struct course {
    std::string name;
    int id;
};

// Function that fetches data from DB
std::vector<course> fetchDataFromDB(){
    std::this_thread::sleep_for(std::chrono::seconds(2)); // simulating a delay of 2 seconds
    return {{"C++ Programming", 255}, {"Programming Languages", 360}};
}

// Worker Thread
void backgroundTask(std::promise<std::string> & msgPromise){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string result = "Finished Retrieving Data!";
    msgPromise.set_value(result);
}

// Add course function to experiment with policies
// Function lets you add a new course to the vector of courses & returns the final courses vector
std::vector<course> addCourse(std::vector<course> courses, std::string name, int id){
    courses.emplace_back(name, id);
    std::this_thread::sleep_for(std::chrono::seconds(2)); // simulating delay
    return courses;
}

int main(){
    // Async task
    std::future<std::vector<course>> futureData =
        std::async(std::launch::async, fetchDataFromDB);

    while(futureData.wait_for(std::chrono::milliseconds(200)) != std::future_status::ready){
        std::cout << "Waiting...\n";
    }

    // Responsiveness
    std::vector<course> courses = futureData.get();

    std::cout << "Courses received: ";
    for (const course& c : courses) {
        std::cout << c.name << "(" << c.id << ") ";
    }

    // Future/Promise
    std::promise<std::string> messagePromise;
    std::future<std::string> messageFuture = messagePromise.get_future();

    std::thread worker(backgroundTask, std::ref(messagePromise));

    std::cout << "\nWaiting for worker...\n";
    std::string message = messageFuture.get();
    std::cout << "Message: " << message << std::endl;

    worker.join();

    // Execution policies experimentation
    // Experimenting with std::launch::async
    std::future<std::vector<course>> result =
    std::async(std::launch::async, addCourse, courses, "Software Engineering", 300); // Function addCourse() is executed and its return type is saved here

    while(result.wait_for(std::chrono::milliseconds(200)) != std::future_status::ready){
    std::cout << "Adding course...\n";}

    courses = result.get(); // this line waits for the function addCourse() to finish computing before retrieving its results

    std::cout << "Courses received: ";
    for (const course& c : courses) {
        std::cout << c.name << "(" << c.id << ") ";
    }

    // Experimenting with std::launch::deferred
    std::future<std::vector<course>> deferredResult =
    std::async(std::launch::deferred, addCourse, courses, "Computer Organization", 220); // function addCourse() is not executed here due to std::launch::deferred

    /*

    If the following block of code is kept, then the loop will infinitely print out "Waiting on deferred..."
    This occurs because the condition waits for the function to finish executing but because the function deferred,
    it will not execute until deferredResult.get() is declared later on.
    */
    /*
    while(deferredResult.wait_for(std::chrono::milliseconds(200)) != std::future_status::ready){
        std::cout << "Waiting on deferred...\n";
    }
    */

    courses = deferredResult.get(); // function addCourse() only executes (and retrieves the respective value) after it gets to this line
    
    std::cout << "\nCourses received: ";
    for (const course& c : courses) {
        std::cout << c.name << "(" << c.id << ") ";
    }

    return 0;
};

/*
The observed difference in behavior when using deferred—specifically is that the task does not start running 
until .get() is declared. std::launch::deferred ensures that the function does not run immediately and is deferred.
*/