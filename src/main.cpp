#include <format>
#include <iostream>

using namespace std;

int sum(int num1, int num2) { return num1 + num2; }

int main() {
  const int a = 5;
  const int b = 6;
  cout << format("Sum of {} and {} is {}", a, b, sum(a, b));

  return 0;
}
