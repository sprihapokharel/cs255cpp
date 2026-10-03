// include the header & expand upon it now

#include "DataBuffer.h" // we wrote this file in the proj dir so it's in " "
#include <stdexcept>
#include <optional>

// define functs from header file
void DataBuffer::add(int value){
    buffer.push_back(value);
}

// sum
int DataBuffer::sum() const {
    int total = 0; // local var to this scope

    for(size_t i = 0; i <= buffer.size(); i++){
        total += buffer[i];
    }

    return total;
}

// get
std::optional<int> DataBuffer::get(size_t index) const {
    if(index >= buffer.size()){
        return std::nullopt;
    }
    return buffer[index];
}

// size
size_t DataBuffer::size() const {
    return buffer.size();
}