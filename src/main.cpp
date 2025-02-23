#include <Parallel/thread_pool.hpp>
#include <iostream>

using namespace std;

int main() {
  auto tp = Parallel::ThreadPool(4);

  cout << "Preparing task\n";

  auto nextFuture = tp.enqueueSimple([]() {
    cout << "Second task is here!\n";
    return 0;
  });

  cout << "Second task queued\n";
  nextFuture.wait();

  cout << "Second task completed with result: " << nextFuture.get() << "\n";
  return 0;
}
