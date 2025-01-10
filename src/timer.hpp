#pragma once
#include <chrono>

class Timer {
 public:
  inline Timer() { start(); }

  inline void start() {
    startTime = std::chrono::system_clock::now();
    isRunning = true;
  }

  inline void stop() {
    endTime = std::chrono::system_clock::now();
    isRunning = false;
  }

  [[nodiscard]]
  inline int64_t elapsedMilliseconds() const {
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;

    auto end = isRunning ? system_clock::now() : endTime;

    return duration_cast<milliseconds>(end - startTime).count();
  }

  [[nodiscard]]
  inline int64_t elapsedMicroseconds() const {
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    using std::chrono::system_clock;

    auto end = isRunning ? system_clock::now() : endTime;

    return duration_cast<microseconds>(end - startTime).count();
  }

  [[nodiscard]]
  inline double elapsedSeconds() const {
    return static_cast<double>(elapsedMilliseconds()) / 1000.0;
  }

 private:
  std::chrono::time_point<std::chrono::system_clock> startTime;
  std::chrono::time_point<std::chrono::system_clock> endTime;

  bool isRunning = false;
};