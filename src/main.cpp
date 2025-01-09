#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

vector<int> runningSum(vector<int>& nums) {
    vector<int> res(nums.size());

    res[0] = nums[0];
    for (size_t i = 1; i < res.size(); i++) {
        res[i] = res[i - 1] + nums[i];
    }
    return res;
}

int main() {
    vector<int> inp = {1, 2, 3, 4};
    auto out = runningSum(inp);

    ranges::copy(out, std::ostream_iterator<int>(std::cout, " "));

    return 0;
}
