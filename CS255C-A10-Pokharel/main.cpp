/*
Name: Spriha Pokharel
Date: 04/06/2026
Assignment 10
Summary: A program where two threads compete to increment the same integer variable.
*/

#include <iostream>
#include <thread>
#include <chrono>

// defining a global integer
int counter = 0;

// function to increment global integer
void incrementCounter(int loops, int threadNum){
    std::cout << "Thread" << threadNum
    << " (ID: " << std::this_thread::get_id()
    << ") started. \n";
    
    for(int i=0; i < loops; i++){
        std::this_thread::sleep_for(std::chrono::microseconds(1));

        int temp = counter;
        temp += 1;
        counter = temp;
    }

    std::cout << "Thread" << threadNum
    << " (ID: " << std::this_thread::get_id()
    << ") finished. \n";
}

int main(){

    // define iterations
    int iterations = 100000;

    // create threads
    std::thread t1 (incrementCounter, iterations, 1);
    std::thread t2 (incrementCounter, iterations, 2);

    // wait to finish
    t1.join();
    t2.join();

    // print the final value
    std::cout << "\nFinal Value: " << counter << std::endl;
    return 0;
}

/*

The final total is inconsistent because both threads access the value at the same time without synchronizing each others
changes. When the threads write their results back, they may overwrite each other and which lead to inconsistent values
being generated.

*/