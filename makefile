CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

TEST_LIST_OBJS = test_stack1.o

test_stack.x: $(TEST_LIST_OBJS)
	$(CXX) $(CXXFLAGS) -o test_stack.x $(TEST_LIST_OBJS)

test_stack1.o: test_stack1.cpp stack.h stack.hpp
	$(CXX) $(CXXFLAGS) -c test_stack1.cpp

clean:
	rm -f *.o test_stack.x

.PHONY: all clean