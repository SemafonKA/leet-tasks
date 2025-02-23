#include <Parallel/thread_pool.hpp>

namespace Parallel {

ThreadPool::ThreadPool(std::size_t nr_workers) {
  stop = false;
  for (auto i = 0ull; i < nr_workers; i++) {
    workers.emplace_back(&ThreadPool::worker, this);
  }
}

void ThreadPool::worker() {
  for (;;) {
    std::function<void()> cur_task;
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [this]() { return stop || !queue.empty(); });

      if (stop && queue.empty()) break;
      if (queue.empty()) continue;

      cur_task = queue.front();
      queue.pop();
      // grab the fx from queue
    }
    cur_task();
  }
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(mtx);
    stop = true;
  }

  cv.notify_all();
  for (auto& worker : workers) {
    worker.join();
  }
}

}  // namespace Parallel
