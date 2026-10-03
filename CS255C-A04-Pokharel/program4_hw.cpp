/*

Name: Spriha Pokharel
Date: 02/15/2026
Summary: A program that explores associative containers like std::map and std::unordered_map alongside the
sequential container std::vector by populating each container with 10,000 entries and evaluating its lookup
complexity and ordering.
External Sources: GeeksforGeeks (https://www.geeksforgeeks.org/cpp/2d-vector-of-pairs-in-c-with-examples/,
                                https://www.geeksforgeeks.org/cpp/map-find-function-in-c-stl/,
                                https://www.geeksforgeeks.org/cpp/how-to-use-unordered_map-efficiently-in-c/)

Notes:

- Going from using std::vector to std::map and std::unordered_map (affect on performance, Big-O)
- Sequential vs. Associative containers
- Performance trade-offs between sorted maps (Red-Black Trees) and unordered maps (Hash Tables)
- Solving a real world data organization problem through pre-defined C++ class templates: Standard Template Library (STL)

*/

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

// Creating & populating three different containers with pairs int (key) and string (value)
int main(){
    // Creating
    std::vector<std::pair<int, std::string>> vec;
    std::map<int, std::string> mp;
    std::unordered_map<int, std::string> ump;

    // Populating
     for(int i = 0; i < 10000; i++){
        std::string value = "Entry" + std::to_string(i);
        vec.push_back({i, value});
        mp [i] = value;
        ump[i] = value;
    }

    // Test loops that search for 10 specific IDs in each container

    // Lookup specific keys
    int searchKeys[10] = {2, 47, 61, 80, 10, 1200, 14, 1600, 180, 9000};

    // Searching the vector
    for (int key: searchKeys){
        auto found = std::find_if(vec.begin(), vec.end(),
    [key] (const std::pair<int, std::string>& p){
        return p.first == key;

    });
    }

    // Searching the map
     for(int key: searchKeys){
        auto found = mp.find(key);
    }

    // Searching the unordered map
     for(int key: searchKeys){
        auto found = ump.find(key);
    }

    // Lookup complexity for Vector: O(N)
    // Lookup complexity for Map: O(log N) (because it uses RB-Tree, and the height of an RB-Tree is log(N))
    // Lookup complexity for Unordered Map: Average Case is O(1)

    // Print the first 5 elements in map
    std::cout << "Printing the first 5 elements in map:" << std::endl;
    int count = 0;
    for(auto const& [key, value] : mp){
        if(count++ == 5) break;
        std::cout << key << ": " << value << std::endl;
    }

    // Print the first 5 elements in unordered map
    std::cout << "Printing the first 5 elements in unordered map:" <<std::endl;
    int count1 = 0;
    for (auto const& [key, value] : ump){
        if (count1++ == 5) break;
        std::cout << key << ": " << value << std::endl;
    }
    return 0;

    /*
    std::map is ordered because it is implemented as a Red-Black Tree. This keeps the elements sorted by key. 
    std::unordered_map does not guarantee any ordering because it is implemented using a hash table.
    */
}




