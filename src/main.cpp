#include <algorithm>
#include <format>
#include <iostream>
#include <sstream>
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

template <typename T>
string to_string(const std::vector<T>& vec) {
  auto oss = std::ostringstream();

  if (vec.empty()) {
    oss << "[]";
    return oss.str();
  }
  oss << format("[ {}", vec[0]);

  bool dotes = false;
  for (size_t i = 1; i < vec.size(); ++i) {
    if (vec.size() > 10 && i >= 5 && i < vec.size() - 5) {
      if (!dotes) {
        oss << ", ...";
        dotes = true;
      }
      continue;
    }
    oss << format(", {}", vec[i]);
  }
  oss << " ]";

  return oss.str();
}

void testFunction(vector<pair<int, vector<int>>>& tests) {
  size_t i = 0;
  for (auto& [expected, testVec] : tests) {
    auto received = hIndex(testVec);

    cout << format("\n Test {}: ", i);
    if (received == expected) {
      cout << format("- pass");
    } else {
      cout << to_string(testVec) << "\n";
      cout << format("  Expected: {}\n", expected);
      cout << format("  Received: {}\n", received);
    }

    ++i;
  }
}

int main() {
  cout << "Warning: Last test is bad for demostration";

  auto tests = vector<pair<int, vector<int>>>();
  tests.push_back({3, {3, 0, 6, 1, 5}});
  tests.push_back({1, {1, 3, 1}});
  tests.push_back({0, {0}});
  tests.push_back({1, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}});

  testFunction(tests);

  return 0;
}
