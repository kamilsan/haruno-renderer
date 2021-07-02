#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

template <typename T>
class Task {
 public:
  virtual ~Task() {}

  virtual T run() = 0;
};

template <typename T>
class ThreadPool {
 public:
  ThreadPool(size_t workers);
  ~ThreadPool();

  std::future<T> addTask(std::unique_ptr<Task<T>> task);
  void close();

 private:
  void thread_function();

  bool closed_;
  std::vector<std::thread> workers_;
  std::queue<std::pair<std::unique_ptr<Task<T>>, std::shared_ptr<std::promise<T>>>> tasks_;
  std::mutex mutex_;
  std::condition_variable tasks_empty_;
  std::condition_variable should_close_;
};

template <typename T>
ThreadPool<T>::ThreadPool(size_t workers) : closed_(false) {
  for (size_t i = 0; i < workers; ++i) {
    workers_.emplace_back(std::thread(std::bind(&ThreadPool::thread_function, this)));
  }
}

template <typename T>
ThreadPool<T>::~ThreadPool() {
  close();

  for (auto& worker : workers_) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

template <typename T>
std::future<T> ThreadPool<T>::addTask(std::unique_ptr<Task<T>> task) {
  std::lock_guard<std::mutex> lock{mutex_};

  auto promise_ptr = std::make_shared<std::promise<T>>();

  tasks_.emplace(std::make_pair(std::move(task), promise_ptr));
  tasks_empty_.notify_one();

  return promise_ptr->get_future();
}

template <typename T>
void ThreadPool<T>::close() {
  closed_ = true;
  tasks_empty_.notify_all();
}

template <typename T>
void ThreadPool<T>::thread_function() {
  std::unique_ptr<Task<T>> task{};
  std::shared_ptr<std::promise<T>> result{};

  while (!closed_) {
    {
      std::unique_lock<std::mutex> lock{mutex_};
      tasks_empty_.wait(lock, [&]() { return !tasks_.empty() || closed_; });
      if (closed_) break;
      auto el = std::move(tasks_.front());
      tasks_.pop();

      task = std::move(el.first);
      result = std::move(el.second);
    }
    result->set_value(task->run());
  }
}

#endif