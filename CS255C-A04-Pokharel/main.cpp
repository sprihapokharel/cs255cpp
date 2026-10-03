#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

// using namespace std; // can use this (makes your code readable), but there are times when you don't want to use them

int main(){
    // make our containers (data structures)
    std::vector<std::pair<int, std::string>> vec; // normal vector won't take a pair, need to specify pair here
    std::map<int, std::string> mp;
    std::unordered_map<int, std::string> ump;

    // (create the 3 containers & populating them) populate the containers: with the key & the values
    for(int i = 0; i < 10; i++){
        std::string value = "Entry" + std::to_string(i);
        vec.push_back({i, value});
        mp [i] = value;
        ump[i] = value;

    }

    // lookup specific keys
    int searchKeys[4] = {2,4,6,8};

    // vector search, still need to write the found function to finish the A04 Assignment
    for (int key: searchKeys){
        auto found = std::find_if(vec.begin(), vec.end(),
    [key] (const std::pair<int, std::string>& p){
        return p.first == key;

    });
    }

    // map search
    for(int key: searchKeys){
        auto found = mp.find(key);
    }

    // print first 5 in map
    std::cout << "Printing first 5 in map!" << std::endl;
    int count = 0;
    for(auto const& [key, value] : mp){
        if(count++ == 5) break;
        std::cout << key << "; " << value << std::endl;
    }
    return 0;
}