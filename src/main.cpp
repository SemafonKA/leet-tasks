#include <vector>

using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  auto i = m - 1;
  auto j = n - 1;
  for (int curr = nums1.size() - 1; curr >= 0; --curr) {
    if (i == -1) {
      nums1[curr] = nums2[j];
      --j;
      continue;
    }
    if (j == -1) {
      nums1[curr] = nums1[i];
      --i;
      continue;
    }
    if (nums1[i] > nums2[j]) {
      nums1[curr] = nums1[i];
      --i;
    } else {
      nums1[curr] = nums2[j];
      --j;
    }
  }
}

int main() {
  constexpr auto greetingsTo = "World";

  return 0;
}
