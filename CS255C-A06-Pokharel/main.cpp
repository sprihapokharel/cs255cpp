/*

Name: Spriha Pokharel
Date: 03/01/2026
Summary: A program that processes a std::vector of a custom Product struct, and performs various
        manipulations on it by using Lambda as custom predicates for into the STL algorithms.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>


// Defining a struct Product with three attributes: name, price, and stock status
struct Product {
        std::string name;
        double price;
        bool inStock;
    };

int main (){
    // Populating the vector products with 8 items
    std::vector<Product> products{
        {"Pen", 2.54, true}, {"Pencil", 5.87, true}, {"Eraser", 1.23, false}, {"Sharpener", 4.00, true}, 
        {"Marker", 15.25, false}, {"Notebook", 10.50, true}, {"Chocolate", 7.25, false}, {"Tape", 9.70, false}
    };

    // Inputting in the price limit on product from the user
    double priceLimit;
    std::cout << "Enter the price limit on products: \n";
    std::cin >> priceLimit;

    // Passing std::count_if into Lambda function to display products below price limit
    auto countLimit = std::count_if(products.begin(), products.end(),
            [priceLimit](const Product& prod) {
                return prod.price < priceLimit;
            });

    std::cout << "\nThere are " << countLimit << " items below the " << priceLimit << " dollar price limit.\n";

    // 
    double totalValue = 0;
    std::for_each(products.begin(), products.end(),
    [&totalValue](const Product& prod){
        if (prod.inStock) {
            totalValue = totalValue + prod.price;
        }
        });

    std::cout << "\nThe total price of every in-stock item is: " << totalValue << " dollars.\n";

    // Getting the original list of products (unsorted)
    std::cout << "\nOriginal list of products: \n";
    for (const auto& prod : products){
        std::cout << prod.name << " ";
    }
    std::cout << "\n";

    // Creating Lambda Function to sort products: inStock -> true before false (descending)
    std::sort(products.begin(), products.end(), [] (const Product& a, const Product& b) {
        if (a.inStock!= b.inStock) {
            return a.inStock > b.inStock;
        }
        return a.price < b.price; // If both products are in stock, sort from lowest to highest price
    });

    // Using another Lambda Function with std::for_each to display final list
    std::cout << "\nList of products (in stock displayed before out of stock): \n";
    std::for_each(products.begin(), products.end(), [](const Product&prod){
        std::cout << prod.name << " ";
    });

    return 0;
};



