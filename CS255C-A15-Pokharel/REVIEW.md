**Name**: Spriha Pokharel  
**Course**: CS255CPP  
**Date**: 05/09/2026

**Sources:**
- C++ Core Guidelines: (https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- https://www.geeksforgeeks.org/cpp/cpp-multithreading-condition-variables/

--- 

## C++ Core Guidelines Review
 
### 1. Guideline: F.16 – For "in" parameters, pass cheaply-copied types by value and others by reference to const
 
**Before:** Vectors were passed by value.
```cpp
T calculateSum(std::vector<T> data)
```
 
**After:** Updated the function to use a const reference to avoid unnecessary copying.
```cpp
T calculateSum(const std::vector<T>& data) const
```
 
---
 
### 2. Guideline ES.71: Prefer a range-for-statement to a for-statement when there is a choice
 
**Before:** Manual indexing was used to iterate through telemetry data.
```cpp
for (int i = 0; i < telemetry.size(); i++) {
    std::cout << telemetry[i] << " ";
}
```
 
**After:** Replacement with a range-based loop.
```cpp
for (const auto& value : telemetry) {
    std::cout << value << " ";
}
```
 
---
 
### 3. Guideline CP.2: Avoid data races
 
**Before:** Shared data was accessed without synchronization.
```cpp
telemetryData->push_back(value);
```
 
**After:** Added mutex protection to ensure thread safety.
```cpp
std::lock_guard<std::mutex> lock(bufferMutex);
telemetryData->push_back(value);
```
 
---
 
## Self-Reflection
 
**What is the most "elegant" part of your code?**
 
The most elegant feature is how the system handles concurrency by separating data creation from data storage. I used std::async to run multiple "Producer" tasks at the same time, while protecting the shared memory with a std::mutex. This ensures that even though many threads are active, the thread-safe buffer prevents data corruption. By leveraging Resource Acquision is Initialization (RAII) with std::lock_guard, the code guarantees that resources are managed safely and locks are released even if an error occurs.
 
**Where does the code still feel "fragile" or "C-style"?**
 
The code feels a little fragile because it creates a new thread for every task, which may not work as well for a system if there are too many producers. Additionally, some logic still relies on manual for loops to process the data, which is a more "C-style" approach. To be more modern, I should replace those loops with STL algorithms.
 
**How would you fix it given more time?**
 
To improve the project, I would replace the manual loops with C++20 Ranges and algorithms to make the data processing more readable. I would also implement a condition variable within the ThreadSafeBuffer so the system can react to new data instantly rather than checking for it repeatedly. Finally, I would refine the C++20 Concepts to provide stricter compile-time validation for telemetry processor requirements.