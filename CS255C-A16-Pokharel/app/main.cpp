/* 
Name: Spriha Pokharel
Course: CS255CPP
Date: 05/09/2026
Assignment #16: The Concurrent Telemetry Processor
Summary: Simulate a high-frequency data environment (through the concurrency telemetry processor) where multiple data
streams must be processed, filtered, and aggregated simulataneously without blocking the main execution thread.

Sources:
https://www.geeksforgeeks.org/cpp/std-future-in-cpp/
https://www.geeksforgeeks.org/cpp/multithreading-in-cpp/
https://en.cppreference.com/cpp/utility/functional/ref
https://eli.thegreenplace.net/2016/the-promises-and-challenges-of-stdasync-task-based-parallelism-in-c11/

*/

/**
 * @file main.cpp
 * @brief Entry point for Concurrent Telemetry Processor system.
 *
 * Demonstrates asynchronous producers generating telemetry data,
 * thread-safe storage, and numeric aggregation using templates.
 */

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

#include "../include/ThreadSafeBuffer.hpp"
#include "../include/Telemetry.hpp"

// simulating telemetry producer
/**
 * @brief Simulates a telemetry data producer running in its own thread.
 *
 * Generates numeric telemetry values and stores them into a shared
 * thread-safe buffer.
 *
 * @param buffer Shared thread-safe buffer for storing telemetry data.
 * @param producerID Identifier for the producer thread.
 * @param iterations Number of telemetry values to generate.
 */
void telemetryProducer(
    ThreadSafeBuffer& buffer,
    int producerID,
    int iterations
)
{
    std::cout << "Producer " << producerID << " started.\n";

    // generate telemetry values
    for(int i = 0; i < iterations; i++)
    {
        double telemetryValue = i * 1.5;

        // store telemetry value
        buffer.addData(telemetryValue);

        // simulate delay
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    std::cout << "Producer " << producerID << " finished.\n";
}

/**
 * @brief Runs the concurrent telemetry simulation.
 *
 * Launches multiple asynchronous producer threads, waits for completion,
 * then aggregates and processes telemetry data using NumericProcessor.
 */
int main()
{
    // shared telemetry buffer
    ThreadSafeBuffer buffer;

    const int telemetryCount = 100;

    // launch producer 1
    std::future<void> producer1 = std::async(std::launch::async, telemetryProducer, std::ref(buffer), 1, telemetryCount);

    // launch producer 2
    std::future<void> producer2 = std::async(std::launch::async, telemetryProducer, std::ref(buffer), 2, telemetryCount);

     // launch producer 3
    std::future<void> producer3 = std::async(std::launch::async, telemetryProducer, std::ref(buffer), 3, telemetryCount);

    while(producer1.wait_for(std::chrono::milliseconds(100))!= std::future_status::ready){
        std::cout << "Processing telemetry...\n";
    }

    // wait for remaining producers
    producer1.get();
    producer2.get();
    producer3.get();

    std::cout
        << "\nAll producers have finished.\n";

    // retrieve telemetry data
    std::vector<double> telemetry =buffer.getData();
    
    for (const auto& value : telemetry) {
    std::cout << value << " ";
    }
    std::cout << "\n";
    

    // create telemetry processor
    NumericProcessor<double> processor;

    std::cout << "\nTelemetry Calculations\n";

    // display total telemetry points
    std::cout << "Telemetry Count: " << telemetry.size() << "\n";

    // display telemetry sum
    std::cout << "Sum: " << processor.calculateSum(telemetry) << "\n";

    // display telemetry average
    std::cout << "Average: " << processor.calculateAverage(telemetry)<< "\n";

    return 0;
}


