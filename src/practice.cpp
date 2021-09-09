#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

static const uint8_t base64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * @param:
 *  - arr: Array of 8-bit unsigned charcter array 
 * @return: Return base64 string
*/
string base64_decode(vector<uint8_t> &arr);

// Takes string to be encoded as input
// and its length and returns encoded string
char *base64Encoder(unsigned char input_str[], int len_str)
{

    // Character set of base64 encoding scheme
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Resultant string
    char *res_str = (char *)malloc(1000 * sizeof(char));

    int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp;
    int i, j, k = 0;

    // Loop takes 3 characters at a time from
    // input_str and stores it in val
    for (i = 0; i < len_str; i += 3)
    {
        val = 0, count = 0, no_of_bits = 0;

        for (j = i; j < len_str && j <= i + 2; j++)
        {
            // binary data of input_str is stored in val
            val = val << 8;

            // (A + 0 = A) stores character in val
            val = val | input_str[j];

            // calculates how many time loop
            // ran if "MEN" -> 3 otherwise "ON" -> 2
            count++;
        }

        no_of_bits = count * 8;

        // calculates how many "=" to append after res_str.
        padding = no_of_bits % 3;

        // extracts all bits from val (6 at a time)
        // and find the value of each block
        while (no_of_bits != 0)
        {
            // retrieve the value of each block
            if (no_of_bits >= 6)
            {
                temp = no_of_bits - 6;

                // binary of 63 is (111111) f
                index = (val >> temp) & 63;
                no_of_bits -= 6;
            }
            else
            {
                temp = 6 - no_of_bits;

                // append zeros to right if bits are less than 6
                index = (val << temp) & 63;
                no_of_bits = 0;
            }
            res_str[k++] = char_set[index];
        }
    }

    // padding is done here
    for (i = 1; i <= padding; i++)
    {
        res_str[k++] = '=';
    }

    res_str[k] = '\0';

    return res_str;
}

unsigned char *read_image(string image, int &len) {
    ifstream file;
    file.open(image, ios::binary);

    unsigned char *data = (unsigned char *)malloc(1000 * sizeof(unsigned char));

    while (!file.eof()) {
        file >> *(data + len);
        len++;
    }

    return data;
}

int main()
{
    // vector<uint8_t> arr = {'T', 'H', 'S'};

    // // expected "VEhT"
    // string ans = base64_decode(arr);
    // cout << ans << "\n";


    // char arr[] = {'T', 'H', 'S'};
    int len = 0;
    unsigned char *arr = read_image("small.png", len);

    for (int i=0; i<len; i++) {
        printf("%02x ", arr[i]);
    }
    cout << "\n";

    cout << base64Encoder(arr, len-1);

    return 0;
}

string base64_decode(vector<uint8_t> &arr)
{
    // write imaplementation here
    size_t len = arr.size();
    uint8_t *pos;
    size_t olen;

    olen = 4 * ((len + 2) / 3); /* 3-byte blocks to 4-byte */

    if (olen < len)
        return string(); /* integer overflow */

    string outStr;
    outStr.resize(olen);

    auto end = arr.end();
    auto in = arr.begin();

    pos = (uint8_t *)&outStr[0];
    while (end - in >= 3)
    {
        *pos++ = base64_table[in[0] >> 2];
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
    }

    if (end - in)
    {
        *pos++ = base64_table[in[0] >> 2];
        if (end - in == 1)
        {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        }
        else
        {
            *pos++ = base64_table[((in[0] & 0x03) << 4) |
                                  (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
    }

    return outStr;
}
