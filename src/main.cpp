#include <array>
#include <iostream>

using namespace std;

bool canConstruct(string ransomNote, string magazine) {
    array<int, 256> chars{0};
    for (const char c : magazine) {
        chars.at(c + 128) += 1;
    }
    for (const char c : ransomNote) {
        if (--chars.at(c + 128) < 0) {
            return false;
        }
    }

    return true;
}

int main() {
    string ransom = "aa";
    string magazine = "aab";
    cout << boolalpha << canConstruct(ransom, magazine);

    return 0;
}
