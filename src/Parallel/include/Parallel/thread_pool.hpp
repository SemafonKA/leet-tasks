#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <set>

namespace Parallel {

class Thread;

class Task {
  friend class Thread;

 public:
  using ID = std::uint64_t;

  enum class Status {
    detached,
    waiting,
    running,
    finished_successfull,
    finished_error,
  };

  [[nodiscard]]
  inline Status getStatus() const {
    std::unique_lock lck(status_mtx);
    return status;
  }
  inline void setStatus(Status newStatus) {
    std::unique_lock lck(status_mtx);
    status = newStatus;
  }

  /**
   * @brief Функция, которая будет выполняться потоком
   */
  virtual void run() = 0;

 private:
  /// !!! Only use it with `status_mtx` !!!
  Status status = Status::detached;
  mutable std::mutex status_mtx;

  /**
   * @brief Функция, которая будет запущена потоком. Вызывает `Task::run()`
   */
  void threadRun();
};

class ThreadPool {
  friend class Thread;

 public:
  /**
   * @brief Инициирует `num_threads` потоков для дальнейшей работы
   */
  void init(std::size_t num_threads);

  /**
   * @brief Добавляет `task` в пул задач для выполнения
   *
   * @return Task::ID - ID-номер добавленной задачи
   */
  [[nodiscard(
      "\n  You can get your completed task back only if you know its ID."
      "\n  Use `_` to ignore this warning if you don't need to know when the "
      "\n    task is done")]]
  Task::ID add_task(std::unique_ptr<Task> task);

  /**
   * @brief Блокирует вызывающий поток, чтобы дождаться выполнения задачи
   * с номером `id`. Возвращает указанную задачу
   */
  [[nodiscard(
      "\n  This function returns you unique_ptr to your task, removing this "
      "\n    task from internal queue. If you ignore this value, you will never"
      "\n    get any values and statuses from your task")]]
  std::unique_ptr<Task> waitAndGet(Task::ID id);

  /**
   * @brief Блокирует вызывающий поток, чтобы дождаться выполнения задачи
   * с номером `id`. НЕ возвращает указанную задачу, сохраняя её в очереди
   */
  void wait(Task::ID id);

  /**
   * @brief Блокирует вызывающий поток, чтобы дождаться выполнения всех задач
   * в очереди задач
   */
  void wait_all();

  /**
   * @brief Проверяет, была ли выполнена задача с номером `id`, не блокируя
   * текущий поток
   */
  bool isCalculated(Task::ID id);

  /**
   * @brief Возвращает `Task::Status` выполнения задачи с номером `id`, не
   * блокируя текущий поток
   */
  Task::Status getTaskStatus(Task::ID id);

  /**
   * @brief Дожидается завершения всех задач и завершает работу `ThreadPool`
   */
  void shutdown();

 private:
  struct TasksQueueItem {
    std::unique_ptr<Task> task;
    Task::ID Id;
  };

  std::queue<TasksQueueItem> tasksQueue;
  std::mutex tasksQueue_mtx;
  std::condition_variable tasksQueue_cv;

  std::set<Task::ID> completedTasksId;
  std::mutex completedTasksId_mtx;
  std::condition_variable completedTasksId_cv;

  std::vector<Thread> threads;

  /// Флаг завершения работы очереди
  std::atomic_bool quite = false;
  /// Номер последней задачи
  std::atomic_uint64_t lastTaskID = 0;
};

}  // namespace Parallel
