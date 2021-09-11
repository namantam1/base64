#include <iostream>

#include "base64.hpp"
using namespace std;

template <class T>
ostream &operator<<(ostream &os, vector<T> &arr) {
    for (auto const &k : arr) os << k << " ";
    return os;
}

int main(int argc, char **argv) {
    // vector<uint8_t> arr = {'N', 'A', 'M'};
    vector<uint8_t> arr = base64::read_file("images/t.txt");

    for (size_t i=0; i<arr.size(); i++) {
        printf("val: %02x %c\n", arr[i], arr[i]);
    }
    cout << "\n";

    // cout << base64::encode(arr) << "\n";
}