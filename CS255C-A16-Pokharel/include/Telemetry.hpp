/*
Name: Spriha Pokharel
Course: CS255CPP
Date: 05/09/2026
Assignment #16: The Concurrent Telemetry Processor
Summary: Header file for Telemetry

Sources:
https://www.geeksforgeeks.org/cpp/header-files-in-c-c-with-examples/
https://www.w3schools.com/cpp/cpp_templates.asp
https://en.cppreference.com/cpp/header/concepts
https://en.cppreference.com/cpp/language/constraints

*/

#pragma once

#include <vector>
#include <numeric>
#include <concepts>
#include <algorithm>
#include <stdexcept>

// template that only allows numeric types
/**
 * @brief Concept that restricts template types to numeric values.
 *
 * Ensures only integral or floating-point types can be used
 * with NumericProcessor.
 */
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// generic telemetry processor
/**
 * @brief Generic telemetry data processor for numeric types.
 *
 * Supports operations like sum and average on a dataset.
 *
 * @tparam T Numeric type (int, float, double, etc.)
 */
template<Numeric T>
class NumericProcessor
{
public:

    // calculate sum
    /**
     * @brief Calculates the sum of telemetry values.
     *
     * @param data Vector of numeric telemetry values.
     * @return Total sum of all values in the vector.
     */
    T calculateSum(const std::vector<T>& data) const
    {
        return std::accumulate(data.begin(), data.end(), static_cast<T>(0));
    }

    // calculate average
    /**
     * @brief Calculates the average of telemetry values.
     *
     * @param data Vector of numeric telemetry values.
     * @return Average value as a double.
     */
    double calculateAverage(
        const std::vector<T>& data
    ) const
    {
        T sum = calculateSum(data);

        return static_cast<double>(sum)
               / data.size();
    }
};