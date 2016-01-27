#include <iostream>
#include <thread>
#include <chrono>
#include "threadsafe_bounded_buffer.hpp"

const int niters = 50;

void consume(int id, ThreadsafeQueue& queue) {
  for (int i = 0; i < niters; ++i) {
    queue.pop();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
  }
}

void produce(int id, ThreadsafeQueue& queue) {
  for (int i = 0; i < niters; ++i) {
    queue.push(id * niters + i);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

int main() {
  ThreadsafeQueue q(10);
  auto t1 = std::chrono::high_resolution_clock::now();
  
  std::thread c1(consume, 1, std::ref(q));
  std::thread c2(consume, 2, std::ref(q));
  std::thread p1(produce, 0, std::ref(q));
  std::thread p2(produce, 1, std::ref(q));
  
  if (c1.joinable())
    c1.join();
  if (c2.joinable())
    c2.join();
  if (p1.joinable())
    p1.join();
  if (p2.joinable())
    p2.join();
  
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
  
  std::cout << "duration is: " << duration << "s\n";
  
  return 0;
}