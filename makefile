CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

TASK1_OBJS = in2post.o

all: in2post.x test_stack.x

in2post.x: $(TASK1_OBJS)
	$(CXX) $(CXXFLAGS) -o in2post.x $(TASK1_OBJS)

in2post.o: in2post.cpp stack.h stack.hpp
	$(CXX) $(CXXFLAGS) -c in2post.cpp

test_stack.x: $(TASK1_OBJS)
	$(CXX) $(CXXFLAGS) -o in2post.x $(TASK1_OBJS)

test_stack.o: test_stack1.cpp stack.h stack.hpp
	$(CXX) $(CXXFLAGS) -c test_stack1.cpp

clean:
	rm -f *.o in2post.x test_stack.x

.PHONY: all clean
