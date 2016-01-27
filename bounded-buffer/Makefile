CXX=clang++
CXXFLAGS=-std=c++11

all: threadsafe_bounded_buffer.o main.cpp
	$(CXX) $(CXXFLAGS) threadsafe_bounded_buffer.o main.cpp -o main

threadsafe_bounded_buffer: threadsafe_bounded_buffer.cpp threadsafe_bounded_buffer.hpp
	$(CXX) $(CXXFLAGS) -c threadsafe_bounded_buffer.cpp

clean:
	rm main *.o
