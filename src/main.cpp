#include <algorithm>
#include <format>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

vector<string> fizzBuzz(int n) {
    vector<string> result(n);

    for (size_t i = 1; i <= n; i++) {
        string str = "";
        if (i % 3 == 0) {
            str += "Fizz";
        }
        if (i % 5 == 0) {
            str += "Buzz";
        }
        if (str.empty()) {
            str = to_string(i);
        }
        result.at(i - 1) = str;
    }

    return result;
}

int main() {
    const int size = 15;
    auto res = fizzBuzz(size);

    ranges::copy(res, ostream_iterator<string>(cout, ", "));

    return 0;
}
