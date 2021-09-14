#include <iostream>

#include "base64.hpp"
using namespace std;

template <class T>
ostream &operator<<(ostream &os, vector<T> &arr) {
    for (auto const &k : arr) os << k << " ";
    return os;
}

int main(int argc, char **argv) {
    // 8-bit array
    vector<uint8_t> arr = {'a', 'b', 'c'};

    // get bas64 string
    string bs64_str = base64::encode(arr);

    // to get base64 of a binary file
    string file_bs64_str = base64::encode(base64::read_file("path/to/binary_file.png"));

    // to get 8-bit array of base64 string
    vector<uint8_t> file_bit_array = base64::decode(bs64_str);

    // base64 string to binary file
    base64::write_file(file_bit_array, "bin_file.png");

    return 0;
}