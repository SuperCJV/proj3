CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

TEST_LIST_OBJS = test_stack1.o
TASK2_OBJS = in2post.o

all: test_stack.x in2post.x

test_stack.x: $(TEST_LIST_OBJS)
	$(CXX) $(CXXFLAGS) -o test_stack.x $(TEST_LIST_OBJS)

in2post.x: $(TASK2_OBJS)
	$(CXX) $(CXXFLAGS) -o in2post.x $(TASK2_OBJS)

test_stack1.o: test_stack1.cpp stack.h stack.hpp
	$(CXX) $(CXXFLAGS) -c test_stack1.cpp

in2post.o: in2post.cpp stack.h stack.hpp
	$(CXX) $(CXXFLAGS) -c in2post.cpp

clean:
	rm -f *.o test_stack.x in2post.x

.PHONY: all clean