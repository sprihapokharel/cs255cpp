/*
Name: Spriha Pokharel
Course: CS255CPP
Date: 05/09/2026
Assignment #16: The Concurrent Telemetry Processor
Summary: Implementation file for ThreadSafeBuffer
*/

#include "../include/ThreadSafeBuffer.hpp"

// constructor
ThreadSafeBuffer::ThreadSafeBuffer()
{
    // create the vector using a smart pointer
    telemetryData = std::make_unique<std::vector<double>>();
}

// add telemetry value
/**
 * @brief Adds a telemetry value to the buffer in a thread-safe manner.
 *
 * Uses a mutex lock to prevent race conditions during concurrent writes.
 *
 * @param value Telemetry value to store.
 */
void ThreadSafeBuffer::addData(double value)
{
    std::lock_guard<std::mutex> lock(bufferMutex);

    telemetryData->push_back(value);
}

// retrieve telemetry data
/**
 * @brief Returns a copy of all stored telemetry data.
 *
 * Thread-safe read operation protected by mutex.
 *
 * @return Copy of internal telemetry vector.
 */
std::vector<double> ThreadSafeBuffer::getData() const
{
    std::lock_guard<std::mutex> lock(bufferMutex);

    // return copy of vector
    return *telemetryData;
}

// retrieve telemetry count
/**
 * @brief Returns the number of stored telemetry values.
 *
 * Thread-safe read operation.
 *
 * @return Number of elements in buffer.
 */
std::size_t ThreadSafeBuffer::size() const
{
    std::lock_guard<std::mutex> lock(bufferMutex);

    return telemetryData->size();
}