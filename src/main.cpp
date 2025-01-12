#include <array>
#include <ios>
#include <iostream>

using namespace std;

bool canConstruct(string s, int k) {
  auto ssize = s.size();
  if (ssize < static_cast<size_t>(k)) {
    return false;
  }
  if (ssize == static_cast<size_t>(k)) {
    return true;
  }

  // Find all letters that are don't have his pairs
  std::array<int, 27> letters = {0};
  for (auto l : s) {
    letters[l - 'a'] ^= 1;
  }

  int countWithoutPairs = 0;
  for (auto l : letters) {
    countWithoutPairs += l;
  }
  return countWithoutPairs <= k;
}

int main() {
  constexpr auto greetingsTo = "World";
  auto s = "tuut";
  cout << std::boolalpha << canConstruct(s, 3) << "\n";

  return 0;
}
