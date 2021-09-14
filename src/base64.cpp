#include "base64.hpp"

#include <fstream>
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

string base64::encode(const vector<uint8_t> &__arr) {
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

vector<uint8_t> base64::decode(const string &__str) {
    vector<uint8_t> __arr;

    return __arr;
}

vector<uint8_t> base64::read_file(const string &__str) {
    vector<uint8_t> __arr;
    ifstream __file;
    __file.open(__str, ios::binary);

    if (!__file.is_open()) {
        cerr << "File: " << __str << " did not found!" << endl;
        exit(EXIT_FAILURE);
    }

    char temp;
    while (__file.read(&temp, sizeof(char))) {
        __arr.push_back(temp);
    }

    __file.close();

    return __arr;
}

void base64::write_file(const vector<uint8_t> &__arr, const string &__str) {
    ofstream __file;
    __file.open(__str, ios::binary);

    for (const auto &el : __arr) __file.write((char *)&el, sizeof(uint8_t));

    __file.close();
}

#ifdef COMPILE_CLI
#include <algorithm>

static void print_help(int exit_code = EXIT_FAILURE) {
    cout << "Usage: base64 [Options]...\n\n";
    cout << "Options:-\n";
    cout << "  -h, --help     Display help\n";
    cout << "  -f, --file     Path to file\n";
    cout << "  -t, --text     Text to encode\n";
    cout << "  -o, --output   Output to given file name\n";
    exit(exit_code);
}

// C++ Command parsing
// https://stackoverflow.com/a/868894/13057978
static char *cmdOption(char **begin, int argc, const string &option) {
    char **end = begin + argc;
    char **itr = find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

static bool cmdExists(char **begin, int argc, const string &option) {
    char **end = begin + argc;
    return find(begin, end, option) != end;
}

static vector<uint8_t> bytesarray(char *__str) {
    int i = 0;
    vector<uint8_t> __res;
    while (__str[i] != '\0') {
        __res.push_back((uint8_t)__str[i++]);
    }

    return __res;
}

int main(int argc, char **argv) {
    // cout << getCmdOption(argv, argv + argc, "-h") << "\n";
    // cout << getCmdOption(argv, argv + argc, "-o") << "\n";

    if (argc >= 2) {
        if (cmdExists(argv, argc, "-h") || cmdExists(argv, argc, "--help"))
            print_help(EXIT_SUCCESS);

        string __base64_ans;
        vector<uint8_t> __bytes_array;

        if (cmdExists(argv, argc, "-t") || cmdExists(argv, argc, "--text")) {
            if (cmdExists(argv, argc, "-t"))
                __bytes_array = bytesarray(cmdOption(argv, argc, "-t"));
            else
                __bytes_array = bytesarray(cmdOption(argv, argc, "-text"));
        }

        else if (cmdExists(argv, argc, "-f") || cmdExists(argv, argc, "--file")) {
            if (cmdExists(argv, argc, "-f"))
                __bytes_array = base64::read_file(cmdOption(argv, argc, "-f"));
            else
                __bytes_array = base64::read_file(cmdOption(argv, argc, "-file"));
        }

        if (__bytes_array.size()) {
            __base64_ans = base64::encode(__bytes_array);
        }

        if (cmdExists(argv, argc, "-o") || cmdExists(argv, argc, "--output")) {
            char *outfile;
            if (cmdExists(argv, argc, "-o"))
                outfile = cmdOption(argv, argc, "-o");
            else
                outfile = cmdOption(argv, argc, "-output");

            ofstream __file;
            __file.open(outfile);
            __file.write(__base64_ans.c_str(), __base64_ans.size());
        } else {
            cout << __base64_ans << "\n";
        }
    } else {
        print_help();
    }
}
#endif  // COMPILE_CLI
