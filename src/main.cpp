#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  auto size = n + m;
  auto res = vector<int>(size);
  auto i = 0;
  auto j = 0;
  for (auto k = 0; k < size; ++k) {
    if (i == m) {
      res[k] = nums2[j];
      ++j;
    } else if (j == n) {
      res[k] = nums1[i];
      ++i;
    } else {
      if (nums2[j] < nums1[i]) {
        res[k] = nums2[j];
        ++j;
      } else {
        res[k] = nums1[i];
        ++i;
      }
    }
  }

  nums1 = std::move(res);
}

int main() {
  constexpr auto greetingsTo = "World";

  return 0;
}
