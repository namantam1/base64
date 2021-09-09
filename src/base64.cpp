#include "base64.hpp"

#include <iostream>
#include <vector>

using namespace std;

// BASE64 Schema table
static const uint8_t BASE64_TABLE[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

string base64::encode(vector<uint8_t> &__arr) {
    string __res;
    size_t padding;

    // Loop takes 3 characters at a time from
    // input_str and stores it in val
    for (size_t i = 0; i < __arr.size(); i += 3) {
        size_t val = 0, count = 0, no_of_bits = 0;

        for (size_t j = i; j < __arr.size() && j <= i + 2; j++) {
            // binary data of input_str is stored in val
            val = val << 8;

            // (A + 0 = A) stores character in val
            val = val | __arr[j];

            // calculates how many time loop
            // ran if "MEN" -> 3 otherwise "ON" -> 2
            count++;
        }

        no_of_bits = count * 8;

        // calculates how many "=" to append after res_str.
        padding = no_of_bits % 3;

        // extracts all bits from val (6 at a time)
        // and find the value of each block
        while (no_of_bits != 0) {
            size_t temp, index;
            // retrieve the value of each block
            if (no_of_bits >= 6) {
                temp = no_of_bits - 6;

                // binary of 63 is (111111) f
                index = (val >> temp) & 63;
                no_of_bits -= 6;
            } else {
                temp = 6 - no_of_bits;

                // append zeros to right if bits are less than 6
                index = (val << temp) & 63;
                no_of_bits = 0;
            }

            __res.push_back(BASE64_TABLE[index]);
        }
    }

    // padding is done here
    for (size_t i = 1; i <= padding; i++) {
        __res.push_back('=');
    }

    return __res;
}
