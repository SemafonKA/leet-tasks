
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

template <typename T>
class container {
  mutable std::mutex m;
  std::vector<T> elements;

 public:
  void add(T element) { add_in(element, true); }

  void addrange(const std::vector<T>& range) {
    std::lock_guard<std::mutex> locker(m);
    for (size_t i = 0; i < range.size(); i++) {
      add_in(range[i], false);
    }
  }

  void dump() const {
    std::lock_guard<std::mutex> locker(m);
    for (auto e : elements) {
      std::cout << e << ", ";
    }
    std::cout << '\n';
  }

 private:
 
  /// Эта функция нужна, чтобы предотвращать threadlock-и
  /// Вместо неё можно было использовать std::recursive_mutex, но он может
  /// вызвать проблемы с работой программы в будущем
  void add_in(T element, bool lock) {
    std::unique_lock<std::mutex> locker(m, std::defer_lock);
    if (lock) {
      locker.lock();
    }
    elements.push_back(element);
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
