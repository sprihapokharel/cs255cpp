/*
Name: Spriha Pokharel
Course: CS255CPP
Date: 05/09/2026
Assignment #16: The Concurrent Telemetry Processor
Summary: Header file for ThreadSafeBuffer

Sources:
https://www.geeksforgeeks.org/cpp/header-files-in-c-c-with-examples/
https://www.geeksforgeeks.org/cpp/std-mutex-in-cpp/
https://www.geeksforgeeks.org/cpp/unique_ptr-in-cpp/

*/

#pragma once

#include <vector>
#include <memory>
#include <mutex>

/**
 * @brief A thread-safe buffer for storing telemetry values.
 *
 * Provides synchronized access for multiple producer threads.
 * Ensures no data races using mutex locking.
 */
class ThreadSafeBuffer{
private:

    // unique ptr to store telemetry values
    std::unique_ptr<std::vector<double>> telemetryData;

    // mutex for the buffer
    mutable std::mutex bufferMutex;

public:

    // constructor
    ThreadSafeBuffer();

    // add telemetry/sensor value to the buffer
    /**
     * @brief Adds a telemetry value to the buffer in a thread-safe way.
     *
     * @param value Numeric telemetry value to store.
     */
    void addData(double value);

    // get the value stored in the buffer
    /**
     * @brief Retrieves a copy of all stored telemetry values.
     *
     * @return Vector containing all stored telemetry data.
     */
    std::vector<double> getData() const;

    // number of values stored
    /**
     * @brief Returns the number of stored telemetry values.
     *
     * @return Number of elements in buffer.
     */
    std::size_t size() const;
};