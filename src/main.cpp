#include <format>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

int jump(vector<int>& nums) {
  int jumps = 0;
  auto size = nums.size();
  int current = size - 1;

  while (current != 0) {
    int maxind = current;
    int hops = 1;
    for (int i = current - 1; i >= 0; --i) {
      if (nums[i] >= hops) {
        maxind = i;
      }
      ++hops;
    }

    current = maxind;
    ++jumps;
  }

  return jumps;
}

void testFunc(std::vector<std::pair<int, std::vector<int>>>& tests) {
  size_t i = 1;
  for (auto& [res, vec] : tests) {
    int received = jump(vec);
    std::cout << format("\nTest {}: ", i);
    std::copy(vec.begin(), vec.end(),
              std::ostream_iterator<int>(std::cout, ", "));
    std::cout << '\n';
    std::cout << format("   Expected: {}\n", res);
    std::cout << format("   Received: {}\n", received);

    i++;
  }
}

int main() {
  auto tests = std::vector<std::pair<int, std::vector<int>>>();
  tests.push_back({2, {2, 3, 1, 1, 4}});
  tests.push_back({2, {2, 3, 0, 1, 4}});

  testFunc(tests);

  return 0;
}
