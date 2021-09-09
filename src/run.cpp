#include "base64.hpp"
#include <iostream>
using namespace std;

int main() {
    vector<uint8_t> arr = {'N', 'A', 'M'};
    cout << base64::encode(arr) << "\n";
}