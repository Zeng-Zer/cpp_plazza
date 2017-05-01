#ifndef BLOCKINGQUEUE_HPP_
# define BLOCKINGQUEUE_HPP_

# include <mutex>
# include <queue>
# include <chrono>
# include <condition_variable>
# include "Option.hpp"

/**
 * Queue that is safe thread
 * block the thread if the queue doesn't contain element to pop
 */
template<typename T>
class BlockingQueue {
public:
  BlockingQueue() = default;
  ~BlockingQueue() = default;

  /**
   * push element into the queue : THREAD SAFE
   */
  void push(T const& elem) {
    {
      std::lock_guard<std::mutex> lock(_mutex);
      _queue.push(elem);
    }
    _condVar.notify_one();
  }

  /**
   * pop element from the queue : THREAD SAFE
   * block the thread if empty
   */
  T pop() {
    std::unique_lock<std::mutex> lock(_mutex);

    _condVar.wait(lock, [this] {
	return !_queue.empty();
      });

    T elem(std::move(_queue.front()));

    _queue.pop();

    return elem;
  }

  /**
   * same as pop() but you can set a timeout in milliseconds
   */
  Option<T> timedPop(int timeout) {
    std::unique_lock<std::mutex> lock(_mutex);

    // if timed out
    if (!_condVar.wait_for(lock, std::chrono::milliseconds(timeout),
			   [this] { return !_queue.empty(); })) {
      return {};
    }

    if (_queue.empty()) {
      return {};
    }
    T elem(std::move(_queue.front()));

    _queue.pop();

    return {elem};
  }

  /**
   * returns queue size
   */
  constexpr size_t size() const {
    return _queue.size();
  }

  /**
   * check if it's empty
   */
  constexpr bool empty() const {
    return _queue.empty();
  }

private:
  std::mutex _mutex;
  std::queue<T> _queue;
  std::condition_variable _condVar;
};

#endif /* !BLOCKINGQUEUE_HPP_ */
