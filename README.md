# Base64
Command line Base64 transcoder utility written in C++

## Tool Used:
- [C++ compiler](https://gcc.gnu.org).
- [Make](https://en.wikipedia.org/wiki/Make_(software))

## How to install and test:

### Installation:

- Clone the repo.
```bash
git clone https://github.com/namantam1/base64
```

- Change directory to src
```bash
cd base64/src/
```

### To use CLI Options

- Compile with cli option to generate executable.

```bash
# Using make
make cli

# Without using make
g++ -DCOMPILE_CLI base64.cpp -o bs64

# Now run following command to get help text and play with cli.
./bs64 -h

# You will get output as -

#Usage: base64 [Options]...
#Options:-
#  -h, --help     Display help
#  -f, --file     Path to file
#  -t, --text     Text to encode
#  -o, --output   Output to given file name
```

### To use as library:

- Get binary object file, compile the base64.cpp with -c Option.
```bash
# Using make
make obj

#without using make
g++ -c base64.cpp -o base64.o
```

- Include base64 as library in your project.
```c++
// example.cpp
#include <iostream>
#include "base64.hpp"

using namespace std;

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
```

- Compile your project with object file generated above.
```bash
g++ base64.o example.cpp -o example

# execute example
./example
```

## TODO
- [x] Implement base64 encode algorithm.
- [x] Implement read binary file and return as 8-bit array.
- [x] Implement command line parser.
- [ ] Handle error and throw proper error with message
- [ ] Implement base64 decode function.
- [ ] Implement write_file function to convert 8-bit array to binary.
- [ ] Write test & benchmarks to get performance idea.
- [ ] Improve encode/decode algorithm.
- [ ] Document encode/decode algorithm.
- [ ] To make this as a Header-Only C++ library.

## Reference

- [Base64 - Wikipedia](https://en.wikipedia.org/wiki/Base64).
- [Blog - What is base64 encoding](https://levelup.gitconnected.com/what-is-base64-encoding-4b5ed1eb58a4).
- [Encode an ASCII string into Base-64 Format](https://www.geeksforgeeks.org/encode-ascii-string-base-64-format/).
- [Base64 C source code](https://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c).

## Licence
[base64](https://github.com/namantam1/base64) source code is licensed under the MIT [Licence](https://github.com/namantam1/base64/blob/main/LICENSE).
