#include <algorithm>
#include <format>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int hIndex(vector<int>& citations) {
  int maxCitations = *std::max_element(citations.begin(), citations.end());
  int numbersSize = std::min(maxCitations, static_cast<int>(citations.size()));
  auto elems = std::vector<int>(numbersSize + 1);

  for (auto citCount : citations) {
    auto val = std::min(citCount, numbersSize);
    if (val == 0) continue;
    elems[val] += 1;
  }

  for (int i = numbersSize; i > 0; --i) {
    if (elems[i] >= i) {
      return i;
    }
    elems[i - 1] += elems[i];
  }

  return elems[0];
}

void testFunction(vector<pair<int, vector<int>>>& tests) {
  size_t i = 0;
  for (auto& [expected, testVec] : tests) {
    auto received = hIndex(testVec);

    cout << format("\n Test {}: [ ", i);
    std::copy(testVec.begin(), testVec.end(),
              std::ostream_iterator<int>(std::cout, ", "));
    cout << "]\n";
    cout << format("  Expected: {}\n", expected);
    cout << format("  Received: {}\n", received);

    ++i;
  }
}

int main() {
  auto tests = vector<pair<int, vector<int>>>();
  tests.push_back({3, {3, 0, 6, 1, 5}});
  tests.push_back({1, {1, 3, 1}});
  tests.push_back({0, {0}});

  testFunction(tests);

  return 0;
}
