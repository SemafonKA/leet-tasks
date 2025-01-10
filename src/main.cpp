
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

template <typename T>
class container {
  mutable std::mutex m;
  std::vector<T> elements;

 public:
  void add(T element) {
    lock();
    elements.pop_back(element);
  }

  void addrange(const std::vector<T>& range) {
    lock();
    elements.insert(elements.end(), range.begin(), range.end());
  }

  void dump() const {
    lock();
    for (auto e : elements) {
      std::cout << e << ", ";
    }
    std::cout << '\n';
  }

 private:
  std::unique_lock<std::mutex> lock() const {
    return std::unique_lock<std::mutex>(m);
  }
};

void threadFunction(container<int>& c) {
  c.addrange({3, rand(), rand(), rand()});
}

int main() {
  srand((unsigned int)time(0));
  container<int> cntr;
  std::thread t1(threadFunction, std::ref(cntr));
  std::thread t2(threadFunction, std::ref(cntr));
  std::thread t3(threadFunction, std::ref(cntr));
  t1.join();
  t2.join();
  t3.join();
  cntr.dump();
  return 0;
}
