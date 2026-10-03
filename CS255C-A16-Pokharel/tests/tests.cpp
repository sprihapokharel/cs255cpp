
/* 
Name: Spriha Pokharel
Course: CS255CPP
Date: 05/09/2026
Assignment #16: The Concurrent Telemetry Processor
Summary: Testing with Catch2

*/

#include <catch2/catch_test_macros.hpp>

#include <future>

#include "../include/ThreadSafeBuffer.hpp"

// test add and retrieve function
TEST_CASE("Integrity Test"){

    ThreadSafeBuffer buffer;

    // add telemetry values
    buffer.addData(10.5);
    buffer.addData(20.5);
    buffer.addData(30.5);

    // retrieve data from buffer
    std::vector<double> data = buffer.getData();

    // check buffer size
    REQUIRE(buffer.size() == 3);

    REQUIRE(data[0] == 10.5);
    REQUIRE(data[1] == 20.5);
    REQUIRE(data[2] == 30.5);
}

// function that threads use to write data
void writeTelemetry(ThreadSafeBuffer& buffer, int iterations){
    for(int i = 0; i < iterations; i++){
        buffer.addData(i);
    }
}

// test thread safety under concurrency
TEST_CASE("Race Condition Test"){

    ThreadSafeBuffer buffer;

    const int iterations = 10000;

    std::future<void> thread1 = std::async(std::launch::async, writeTelemetry, std::ref(buffer), iterations);

    std::future<void> thread2 = std::async(std::launch::async, writeTelemetry, std::ref(buffer), iterations);

    thread1.get();
    thread2.get();

    REQUIRE(buffer.size() == 20000);
}