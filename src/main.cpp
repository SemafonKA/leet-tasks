#include <format>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/// Time: O(N), Space: O(log(N))
/// Work with any majority element in the array
int majorityElement(vector<int>& nums) {
  auto counts = std::map<int, int>();
  for (auto num : nums) {
    counts[num] += 1;
  }

  int maxNum = nums[0];
  int maxCount = 0;
  for (const auto& [num, count] : counts) {
    if (count > maxCount) {
      maxNum = num;
      maxCount = count;
    }
  }

  return maxNum;
}

/// Time: O(N), Space: O(1)
/// Works only if majority element is appear more than N/2 times
auto majorityBoyerMoore(vector<int>& nums) {
  int count = 0;
  int maj;
  maj = nums[0];
  for (int i = 0; i < nums.size(); i++) {
    if (count == 0) {
      maj = nums[i];
    }
    count += (nums[i] == maj) ? 1 : -1;
  }
  if (count >= 0) {
    return maj;
  }

  return -1;
}

int main() {
  auto nums = vector<int>{1, 1, 2, 2, 3, 2, 2};
  std::cout << std::format("My approach: {}, Boyer Moore: {}\n",
                           majorityElement(nums), majorityBoyerMoore(nums));
  return 0;
}
