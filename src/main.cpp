#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class FooBar {
 private:
  int n;
  bool isFooTurn = true;
  condition_variable cv;
  std::mutex m;

 public:
  FooBar(int n) { this->n = n; }

  void foo(function<void()> printFoo) {
    std::unique_lock lock(m);
    for (int i = 0; i < n; i++) {
      cv.wait(lock, [&] { return isFooTurn; });
      printFoo();
      isFooTurn = false;
      cv.notify_all();
    }
  }

  void bar(function<void()> printBar) {
    std::unique_lock lock(m);
    for (int i = 0; i < n; i++) {
      cv.wait(lock, [&] { return !isFooTurn; });
      printBar();
      isFooTurn = true;
      cv.notify_all();
    }
  }
};

int main() {
  FooBar fooBar(2);
  std::atomic_int threadCount = 2;

  auto thr1 = std::thread(
      [](FooBar& fb, std::atomic_int& tc) {
        fb.foo([] { cout << "Foo"; });
        --tc;
      },
      std::ref(fooBar), std::ref(threadCount));

  auto thr2 = std::thread(
      [](FooBar& fb, std::atomic_int& tc) {
        fb.bar([] { cout << "Bar"; });
        --tc;
      },
      std::ref(fooBar), std::ref(threadCount));

  while (threadCount.load() > 0) {
    std::this_thread::yield();
  }

  thr1.join();
  thr2.join();

  return 0;
}
