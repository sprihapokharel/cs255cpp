#pragma once // want it to load once
#include <vector> // built-in arrays
#include <optional> // funct is optional (allows us to do that)

// all #includes are header files that live somewhere else


class DataBuffer {
    //variables
    private:
        std::vector<int> buffer;


    //functions: add() sum() get() size()
    public:
        void add(int value)
        int sum() const;
        std::optional<int> get(size_t index) const;
        size_t size() const;
};

