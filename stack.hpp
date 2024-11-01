#ifndef STACK_HPP
#define STACK_HPP
// Prevents multiple inclusions of the file during compilation

#include <iostream>
#include <vector>
#include "stack.h"

using namespace std;

//----------------------------------------
// ====== Constructors & Destructors =====
//----------------------------------------

// Default Constructor
// Uses default constructor to initialize empty vector
template<typename T>
    Stack<T>::Stack() = default;

// Deconstructor
// Automatically deallocates the vector 
template<typename T>
    Stack<T>::~Stack() = default;

// Copy Constructor
// Creates a new stack with data_ initialized as a copy of rhs.data
template<typename T>
    Stack<T>::Stack(const Stack<T>& rhs) : data_(rhs.data_) {}

// Move Constructor
// Initializes data_ by moving rhs.data_
template<typename T>
    Stack<T>::Stack(Stack<T>&& rhs) : data_(move(rhs.data_)) {}

// Copy Assignment operator
// Assigns rhs.data_ to data_ 
template<typename T>
    Stack<T>& Stack<T>::operator= (const Stack <T>& rhs)
    {
        if(this != &rhs){   // Performs deep copy if rhs is not the same object as this
            data_ = rhs.data_;
        }
        return *this;
    }

// Move Constructor
// Transfers ownership of rhs.data
template<typename T>
    Stack<T>& Stack<T>::operator=(Stack<T>&& rhs)
    {
        if(this != &rhs){
            data_ = move(rhs.data_);
        }
    }

//----------------------------------------
// =========== Member functions ==========
//----------------------------------------

// Checks is stack is empty
template<typename T>
    bool Stack<T>::empty() const{
        return data_.empty();
    }

// Clears stack by clearing data_
template<typename T>
    void Stack<T>::clear()
    {
        data_.clear();
    }

// Adds x to stack by appending it to the end of data_
template<typename T>
    void Stack<T>::push(const T& x)
    {
        data_.push_back(x);
    }

// Adds x to data_ by moving to avoid unnecessary copying
template<typename T>
    void Stack<T>::push(T && x)
    {
        data_.push_back(move(x));
    }

// Removes the last element of data_ if the stack is not empty
template<typename T>
    void Stack<T>::pop()
    {
        if(!empty()){
            data_.pop_back();
        }
    }

// Returns a reference to the last element of data_ if it's not empty
template<typename T>
    T& Stack<T>::top()
    {
        if(!empty()){
            return data_.back();
        } else{
            throw std::out_of_range("Stack is empty");
        }
    }

// Returns a const reference (meaning the returned value will not be modified) to the last element of data_ if it's not empty
template<typename T>
    const T& Stack<T>::top() const
    {
        if(!empty()){
            return data_.back();
        } else{
            throw std::out_of_range("Stack is empty");
        }
    }

// Returns the number of elements in the stack
template<typename T>
    int Stack<T>::size() const
    {
        return data_.size();
    }

// Prints elements from top to bottom
template<typename T>
    void Stack<T>::print(std::ostream& os, char ofc) const {
        for (auto elem = data_.rbegin(); elem != data_.rend(); ++elem) {    // itereates from rbegin() to rend()
            os << *elem;
            if (elem + 1 != data_.rend()){
                os << ofc;  // Adds ofc between elements
            }
        }
    }

//----------------------------------------
// ===== Non-Member global functions =====
//----------------------------------------

// Outputs teh stack to os by calling print()
template <typename T>
    std::ostream& operator<< (std::ostream& os, const Stack<T>& a) {
        a.print(os);
        return os;
    }

// Compares data_ of both stacks a and b using get_data()
template <typename T>
    bool operator==(const Stack<T>& a, const Stack<T>& b) {
        return a.get_data() == b.get_data();
    }

// Returns the negation of operator==
template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
    return !(a == b);
}

// Compares elements from top to bottom
// If any element a is greater than the corresponding elemtn b, return false
// Otherwise, returns true
template <typename T>
    bool operator<=(const Stack<T>& a, const Stack<T>& b) {
        auto a_elem = a.get_data_rbegin();
        auto b_elem = b.get_data_rbegin();
        
        while (a_elem != a.get_data_rend() && b_elem != b.get_data_rend()) {
            if (*a_elem > *b_elem) {
                return false;
            }
            ++a_elem;
            ++b_elem;
        }
        return a_elem == a.get_data_rend();
    }

#endif