#include <iostream>
#include <vector>

using namespace std;

// С точки зрения практичности, решение как будто бы неплохое.
// На выходе получаем все точки и точно знаем, где будет макс прибыль.
// Но чёрт возьми слишком громоздкое, да и по памяти место занимает.
int maxProfit(vector<int>& prices) {
  std::vector<std::pair<int, int>> minmaxes;
  int min = 0;
  int max = -1;

  // Сохраняем все инфинумы-экстремумы
  for (size_t i = 1; i < prices.size(); i++) {
    if (max == -1) {
      if (prices[min] >= prices[i]) {
        min = i;
      } else {
        max = i;
      }
      continue;
    }

    if (prices[max] <= prices[i]) {
      max = i;
    } else {
      minmaxes.push_back(std::make_pair(min, max));
      min = i;
      max = -1;
    }
  }

  // В случае, если нашли максимум, но спуска вниз не было
  if (max != -1) {
    minmaxes.push_back(std::make_pair(min, max));
  }

  // Идём с конца и получаем максимумы для предыдущих пар чисел
  // (поскольку максимум справа подходит для левого минимума)
  for (int i = static_cast<int>(minmaxes.size()) - 1; i > 0; --i) {
    auto& curr = minmaxes[i];
    auto& prev = minmaxes[i - 1];
    if (prices[curr.second] > prices[prev.second]) {
      prev.second = curr.second;
    }
  }

  // Перебираем все мини-максные пары, находим максимальную выгоду
  auto maxDelta = 0;
  for (size_t i = 0; i < minmaxes.size(); i++) {
    auto& curr = minmaxes[i];
    maxDelta = std::max(prices[curr.second] - prices[curr.first], maxDelta);
  }

  return maxDelta;
}

// Решение с O(1) по памяти, простое, пусть и ничего не запоминает.
// Но задача этого и не требовала.
//
// Я не смог до него догадаться, потому что изначально начал смотреть на поиск
// минимума и максимума, и с таким подходом их найти было невозможно.
// А вот найти минимум и максимальный профит, вот это вполне себе рабочая схема.
int maxProfitSimple(vector<int>& prices) {
  int min_price = prices[0];
  int maxprof = 0;

  for (int i = 1; i < prices.size(); i++) {
    maxprof = max(maxprof, prices[i] - min_price);
    min_price = min(prices[i], min_price);
  }
  return maxprof;
}

std::ostream& operator<<(std::ostream& os, const vector<int>& v) {
  os << "[" << v[0];
  for (size_t i = 0; i < v.size(); i++) {
    os << v[i] << ",";
  }
  os << "]";
  return os;
}

int main() {
  auto test1 = vector<int>{7, 1, 5, 3, 6, 4};
  auto test2 = vector<int>{7, 6, 4, 3, 1};
  auto test3 = vector<int>{};
  std::cout << "Max profit 1: " << maxProfit(test1) << "\n";

  return 0;
}
