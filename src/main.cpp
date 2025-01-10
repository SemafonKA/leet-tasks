#include <format>
#include <future>
#include <iostream>
#include <numeric>

#include "timer.hpp"

using namespace std;

template <typename RandomIt> int parallel_sum(RandomIt beg, RandomIt end) {
    auto len = end - beg;
    if (len < 2'000'000) {
        return std::accumulate(beg, end, 0);
    }
    auto mid = beg + len / 2;
    auto handle = std::async(std::launch::async, parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}

int main() {
    std::vector<int> v(10000000, 1);
    auto timer = Timer();

    cout << "One thread sum\n";
    timer.start();
    auto res = std::accumulate(v.begin(), v.end(), 0);
    timer.stop();
    cout << format("    Result: {}, time: {} micros\n", res, timer.elapsedMicroseconds());

    cout << "Multi threads sum\n";
    timer.start();
    res = parallel_sum(v.begin(), v.end());
    timer.stop();
    cout << format("    Result: {}, time: {} micros\n", res, timer.elapsedMicroseconds());

    return 0;
}
