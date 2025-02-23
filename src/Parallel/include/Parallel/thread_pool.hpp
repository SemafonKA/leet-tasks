#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace Parallel {

class ThreadPool {
 public:
  ThreadPool(std::size_t nr_threads = std::thread::hardware_concurrency());
  ~ThreadPool();

  template <typename F>
  auto enqueue(F&& callback) -> std::future<decltype(callback())>;

  ThreadPool(ThreadPool&&) = delete;
  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(ThreadPool&&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

 private:
  std::vector<std::thread> workers;
  std::mutex mtx;
  std::condition_variable cv;
  std::queue<std::function<void()>> queue;
  void worker();
  bool stop;
};

template <typename F>
auto ThreadPool::enqueue(F&& callback) -> std::future<decltype(callback())> {
  using retType = decltype(callback());
  auto task_ptr = std::make_shared<std::packaged_task<retType()>>(callback);

  auto future_object = task_ptr->get_future();
  {
    auto lock = std::unique_lock(mtx);
    queue.emplace([task_ptr]() { (*task_ptr)(); });
  }

  cv.notify_one();
  return future_object;
}

}  // namespace Parallel
