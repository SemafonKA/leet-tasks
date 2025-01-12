#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int>& nums, int val) {
  int k = nums.size();
  for (int i = 0; i < k; ++i) {
    if (nums[i] == val) {
      nums[i--] = nums[--k];
    }
  }
  return k;
}

int main() {
  constexpr auto greetingsTo = "World";

  return 0;
}
