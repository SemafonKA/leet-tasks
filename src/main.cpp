#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/// Time: O(n log(n)) (O(n2) worst), Space: O(1)
void rotate1(vector<int>& nums, int k) {
  int len = static_cast<int>(nums.size());
  k = k % len;
  for (int i = 0; i < k; i++) {
    auto last = nums[len - 1];
    for (int j = len - 1; j > 0; --j) {
      nums[j] = nums[j - 1];
    }
    nums[0] = last;
  }
}

/// Time: O(n), Space: O(1)
void rotate2(vector<int>& nums, int k) {
  k = k % nums.size();
  // revert all array
  std::reverse(nums.begin(), nums.end());
  // reverce first part [0; k]
  std::reverse(nums.begin(), nums.begin() + k);
  // reverce last part [k+1; n]
  std::reverse(nums.begin() + k, nums.end());
}

/// Time: O(n), Space: O(n)
void rotate3(vector<int>& nums, int k) {
  k = k % nums.size();
  vector<int> tmp(k);
  std::copy(nums.end() - k, nums.end(), tmp.begin());
  std::copy(nums.begin(), nums.end() - k, nums.begin() + k);
  std::copy(tmp.begin(), tmp.end(), nums.begin());
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec) {
  os << "[" << vec[0];
  for (size_t i = 1; i < vec.size(); ++i) {
    os << "," << vec[i];
  }
  os << "]";

  return os;
}

int main() {
  auto test = std::vector<int>{1, 2, 3, 4, 5, 6, 7};
  auto k = 3;

  auto res1 = test;
  rotate1(res1, k);
  std::cout << "Rotate 1: " << res1 << '\n';

  auto res2 = test;
  rotate2(res2, k);
  std::cout << "Rotate 2: " << res2 << '\n';

  auto res3 = test;
  rotate3(res3, k);
  std::cout << "Rotate 3: " << res3 << '\n';

  return 0;
}
