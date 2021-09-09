#include <iostream>
#include <vector>
using namespace std;

/**
 * @param:
 *  - arr: Array of 8-bit unsigned charcter array 
 * @return: Return base64 string
*/
string base64_decode(vector<uint8_t> &arr);

int main()
{
    vector<uint8_t> arr = {'T', 'H', 'S'};

    // expected "VEhT"
    string ans = base64_decode(arr);
    cout << ans << "\n";

    return 0;
}

string base64_decode(vector<uint8_t> &arr) {
    // write imaplementation here
}
