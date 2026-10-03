#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

// shared resource variable
int accountBalance = 0;

// mutex object to protect var
std::mutex balanceMutex;

// function that locks access
// pretend deposit into bank
void deposit(int amount, int repetitions){ // using kinda RAII, newer concept, simple version of that
    for (int i = 0; i < repetitions; i++){
        std::lock_guard<std::mutex> lock(balanceMutex); // will lock/unlock account balance accordingly
        accountBalance += amount;
    }
}

// pretend withdraw function
void withdraw(int amount, int repetitions){
    for (int i=0; i < repetitions; i++){
        std::unique_lock<std::mutex> lock(balanceMutex);
        accountBalance -= amount;
        lock.unlock();

        // create delay
        std::this_thread::sleep_for(std::chrono::microseconds(1));

        // lock again
        lock.lock();

    }
}

int main(){
    // 100k iterations
    const int iterations = 100000;

    // make our vector of threads
    std::vector<std::thread> threads;

    // deposit threads
    threads.emplace_back(deposit, 1, iterations);
    threads.emplace_back(deposit, 1, iterations);

    // withdraw threads
    threads.emplace_back(withdraw, 1, iterations);
    threads.emplace_back(withdraw, 1, iterations);

    // join all threads together
    for(auto &t : threads){
        t.join();
    }

    // expected result is zero - we deposited and withdrawed teh same amount
    std::cout << "Final Account Balance: " << accountBalance << std::endl;

    return 0;
}



/*

std unique lock: lets us unlock and lock manually
    - can use for intensive things

lockguard does it automatically for us

- may not be done in sequence (depo, depo, wihdraw, withdraw, etc.)
- if you want the final balance to not be 0, you can just change the deposit and withdraw amounts

*/





