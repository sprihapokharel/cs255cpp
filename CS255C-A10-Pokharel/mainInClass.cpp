#include <iostream>
#include <thread>
#include <chrono>

//shared variable
int sharedValue = 0;

//function to edit the shared var
void addToValue(int loops, int threadNum){
    std::cout << "Thread" << threadNum
    << " (ID: " << std::this_thread::get_id()
    << ") started. \n";

    for(int i=0; i < loops; i++){
        //force interleaving
        std::this_thread::sleep_for(std::chrono::microseconds(1));

        int temp = sharedValue;
        temp += 1;
        sharedValue = temp;
    }

    std::cout << "Thread" << threadNum
    << " (ID: " << std::this_thread::get_id()
    << ") finished. \n";
}   

int main(){

    //define iterations
    int iterations = 100000;

    //create threads
    std::thread t1(addToValue, iterations, 1);
    std::thread t2(addToValue, iterations, 2);

    //wait to finish
    t1.join();
    t2.join();

    //print final value (expecting 200000,
    // but race condition might make it less)
    std::cout << "\nFinal Value: " << sharedValue << std::endl;
    return 0;
}