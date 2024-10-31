#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "stackc.hpp"

namespace cop4530 {

template <typename T>
class Stack {
public:
    Stack();
    ~Stack();
    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other) noexcept;
    Stack<T>& operator=(const Stack<T>& other);
    Stack<T>& operator=(Stack<T>&& other) noexcept;

    bool empty() const;
    void clear();
    void push(const T& x);
    void push(T&& x);
    void pop();
    T& top();
    const T& top() const;
    int size() const;
    void print(std::ostream& os, char ofc = ' ') const;

private:
    std::vector<T> data_;
};

// Non-member functions
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack);

template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b);

template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b);

template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b);

} // namespace cop4530

#endif
