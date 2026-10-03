/*
Name: Spriha Pokharel
Date: 04/11/2026
Assignment: #11
Summary: Using previously developed (Week 10) counter program to prevent data races
         and ensure it is thread-safe.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

// global counter
int counter = 0;

// mutex to protect counter
std::mutex counterMutex;

// increment function
void incrementCounter(int loops){
    for(int i = 0; i < loops; i++){
        std::lock_guard<std::mutex> lock(counterMutex);
        counter++;  
    }
}

// decrement function
void decrementCounter(int loops){
    for(int i = 0; i < loops; i++){
        std::unique_lock<std::mutex> lock(counterMutex);
        counter--;

        lock.unlock();
        
        // create delay
        std::this_thread::sleep_for(std::chrono::microseconds(1));

        // lock again
        lock.lock();

        /*
        We would use std::unique_lock over std::lock_guard in scenarios involving sleep or long-running non-critical sections
        because it std::unique_lock allows us to lock and unlock manually whereas std::lock_guard automatically does it.
        */

    }
}

int main(){

    const int iterations = 200000;

    std::vector<std::thread> threads;

    threads.emplace_back(incrementCounter, iterations);

    threads.emplace_back(decrementCounter, iterations);

    // join threads
    for(auto &t : threads){
        t.join();
    }

    // print result: expected is 0.
    std::cout << "Final Value: " << counter << std::endl;

    return 0;
}

/*

Describe a scenario where two threads could cause a deadlock using two different mutexes.
A deadlock occurs when two different threads each hold a mutex while attempting to access the
mutex the other one has; resulting in both being stuck as they both wait for each other to release
its mutex.

Mention which C++17 feature (e.g., std::scoped_lock) could be used to prevent this scenario.
std::scoped_lock could be used to prevent this scenario as it allows for multiple mutexes to be locked
at once, which avoids deadlock (both mutexes are acquired together).

*/