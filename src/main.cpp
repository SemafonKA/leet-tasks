#include <iostream>
#include <vector>

using namespace std;

int removeDuplicates(vector<int>& nums) {
  int k = 2;
  for (int i = 2; i < nums.size(); ++i) {
    if (nums[k - 2] == nums[k - 1] && nums[k - 1] == nums[i]) {
      continue;
    }
    nums[k] = nums[i];
    k += 1;
  }
  return min(k, static_cast<int>(nums.size()));
}

int main() {
  constexpr auto greetingsTo = "World";

  return 0;
}
