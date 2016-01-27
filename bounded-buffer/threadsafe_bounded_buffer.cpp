//
//  threadsafe_bounded_buffer.cpp
//  cpp-concurrency
//
//  Created by Minh Pham on 1/27/16.
//  Copyright © 2016 Minh Pham. All rights reserved.
//

#include "threadsafe_bounded_buffer.hpp"

ThreadsafeQueue::ThreadsafeQueue(int capacity)
    : head(0),
      tail(0),
      size(0),
      capacity(capacity) {
  buf = new int[capacity];
}

ThreadsafeQueue::~ThreadsafeQueue() {
  delete[] buf;
}

void ThreadsafeQueue::push(int x) {
  std::unique_lock<std::mutex> lock(mtx);
  condnotfull.wait(lock, [&]() { return size <= capacity; });

  buf[tail] = x;
  tail = (tail + 1) % capacity;
  ++size;
  std::cout << "+ " << x << "\n";

  condnotempty.notify_one();
}

int ThreadsafeQueue::pop() {
  std::unique_lock<std::mutex> lock(mtx);
  condnotempty.wait(lock, [&]() { return size > 0; });

  int res = buf[head];
  head = (head + 1) % capacity;
  --size;
  std::cout << "        - " << res << "\n";

  condnotfull.notify_one();

  return res;
}
