#ifndef STACK_HPP
#define STACK_HPP

#include "stack.h"
#include <vector>
#include <stdexcept>

namespace cop4530 {

template <typename T>
Stack<T>::Stack() = default;

template <typename T>
Stack<T>::~Stack() = default;

template <typename T>
Stack<T>::Stack(const Stack<T>& other) : data_(other.data_) {}

template <typename T>
Stack<T>::Stack(Stack<T>&& other) noexcept : data_(std::move(other.data_)) {}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        data_ = other.data_;
    }
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
    }
    return *this;
}

template <typename T>
bool Stack<T>::empty() const {
    return data_.empty();
}

template <typename T>
void Stack<T>::clear() {
    data_.clear();
}

template <typename T>
void Stack<T>::push(const T& x) {
    data_.push_back(x);
}

template <typename T>
void Stack<T>::push(T&& x) {
    data_.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) throw std::out_of_range("Stack is empty");
    data_.pop_back();
}

template <typename T>
T& Stack<T>::top() {
    if (empty()) throw std::out_of_range("Stack is empty");
    return data_.back();
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) throw std::out_of_range("Stack is empty");
    return data_.back();
}

template <typename T>
int Stack<T>::size() const {
    return data_.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
    for (auto it = data_.rbegin(); it != data_.rend(); ++it) {
        os << *it;
        if (it + 1 != data_.rend()) os << ofc;
    }
}

// Non-member functions
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    stack.print(os);
    return os;
}

template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b) {
    return a.data_ == b.data_;
}

template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
    return !(a == b);
}

template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b) {
    auto ait = a.data_.rbegin();
    auto bit = b.data_.rbegin();
    
    while (ait != a.data_.rend() && bit != b.data_.rend()) {
        if (*ait > *bit) return false;
        ++ait;
        ++bit;
    }
    return ait == a.data_.rend();
}

} // namespace cop4530

#endif
