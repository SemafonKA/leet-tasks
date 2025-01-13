#include <format>
#include <iostream>
#include <vector>

using namespace std;

int maxProfitSimple(vector<int>& prices) {
  int maxProfit = 0;
  for (size_t i = 0; i < prices.size() - 1; ++i) {
    maxProfit += std::max(prices[i + 1] - prices[i], 0);
  }
  return maxProfit;
}

int main() {
  auto test1 = vector<int>{7, 1, 5, 3, 6, 4};
  auto test2 = vector<int>{7, 6, 4, 3, 1};
  auto test3 = vector<int>{1, 2, 3, 4, 5};
  auto test4 = vector<int>{3, 3, 5, 0, 0, 3, 1, 4};

  std::cout << "\n\n***** MAX PROFIT 2 *****\n\n";

  std::cout << std::format("Test1: expected: {}, got {}\n", 7,
                           maxProfitSimple(test1));
  std::cout << std::format("Test2: expected: {}, got {}\n", 0,
                           maxProfitSimple(test2));
  std::cout << std::format("Test3: expected: {}, got {}\n", 4,
                           maxProfitSimple(test3));
  std::cout << std::format("Test4: expected: {}, got {}\n", 8,
                           maxProfitSimple(test4));

  return 0;
}
