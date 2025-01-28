#include <format>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

bool canJump(vector<int>& nums) {
  size_t currentPos = nums.size() - 1;
  size_t hopsCount = 0;

  for (int64_t index = currentPos - 1; index >= 0; --index) {
    ++hopsCount;

    if (hopsCount <= nums[index]) {
      hopsCount = 0;
      currentPos = index;
      continue;
    }
  }

  if (currentPos == 0) {
    return true;
  }
  return false;
}

void testFunction(std::vector<std::pair<bool, std::vector<int>>>& testCases) {
  size_t i = 1;
  for (auto& test : testCases) {
    cout << std::format("Test case {}\n", i);
    cout << std::format("\tExpected: {}\n", test.first);
    cout << std::format("\tActually: {}\n\n", canJump(test.second));
  }
}

int main() {
  auto tests = std::vector<std::pair<bool, std::vector<int>>>();

  tests.push_back({true, {2, 3, 1, 1, 4}});
  tests.push_back({false, {3, 2, 1, 0, 4}});

  testFunction(tests);

  return 0;
}
