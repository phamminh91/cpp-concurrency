//
//  threadsafe_bounded_buffer.hpp
//  cpp-concurrency
//
//  Created by Minh Pham on 1/27/16.
//  Copyright © 2016 Minh Pham. All rights reserved.
//

#ifndef threadsafe_bounded_buffer_hpp
#define threadsafe_bounded_buffer_hpp

#include <cstdlib>
#include <iostream>
#include <mutex>
#include <vector>

class ThreadsafeQueue {
public:
  ThreadsafeQueue(int capacity);
  ~ThreadsafeQueue();
  void push(int x);
  int pop();
  
private:
  std::mutex mtx;
  std::condition_variable condnotfull;
  std::condition_variable condnotempty;
  const int capacity;
  int *buf;
  int head;
  int tail;
  int size;
};

#endif /* threadsafe_bounded_buffer_hpp */
