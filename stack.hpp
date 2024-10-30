#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <vector>
#include "stack.h"

//----------------------------------------
// ====== Constructors & Destructors =====
//----------------------------------------

//Stack():
template<typename T>
    Stack<T>::Stack()
    {
        // Initialize stack
        stackSize = 0;
        head = nullptr;
    }

//~Stack ():
template<typename T>
    Stack<T>::~Stack()
    {
        clear();
        delete head;
    }

//Stack (const Stack<T>&):
template<typename T>
    Stack<T>::Stack(const Stack<T> &rhs)
    {
        // Initialize stack
        stackSize = 0;
        head = nullptr;

        // Deep copy other stack to this one
        copyFrom(rhs);
    }

//Stack(Stack<T> &&):
template<typename T>
    Stack<T>::Stack(Stack<T>&& rhs)
    {
        // head and stackSize points to other head and stackSize
        head = rhs.head;
        stackSize = rhs.stackSize;

        // Re-initialize other stack to empty state
        rhs.head = nullptr;
        rhs.stackSize = 0;
    }

//Stack<T>& operator= (const Stack <T>&):
template<typename T>
    Stack<T>& Stack<T>::operator= (const Stack <T>& rhs)
    {
        if(this != &rhs){
            clear();
            copyFrom(rhs);
        }
        return *this;
    }

//Stack<T> & operator=(Stack<T> &&):
template<typename T>
    Stack<T>& Stack<T>::operator=(Stack<T> && rhs)
    {
        if(this != &rhs){
            clear();
            // head and stackSize points to other head and stackSize
            head = rhs.head;
            stackSize = rhs.stackSize;

            // Re-initialize other stack to empty state
            rhs.head = nullptr;
            rhs.stackSize = 0;
        }
    }

//----------------------------------------
// =========== Member functions ==========
//----------------------------------------

//bool empty() const:
template<typename T>
    bool Stack<T>::empty() const{
        return stackSize==0;
    }

//void clear():
template<typename T>
    void Stack<T>::clear()
    {
        while(!empty()){
            pop();
        }
    }

//void push(const T& x):
template<typename T>
    void Stack<T>::push(const T& x)
    {
        head = new Node(x, head);
        ++stackSize;
    }

//void push(T && x):
template<typename T>
    void Stack<T>::push(T && x)
    {
        head = new Node(std::move(x), head);
        ++stackSize;
    }

//void pop():
template<typename T>
    void Stack<T>::pop()
    {
        if(!empty()){
            Node* temp = tail;
            head = head->next;
            delete temp;
            --stackSize;
        }
    }

//T& top():
template<typename T>
    T& Stack<T>::top()
    {
        if(!empty){
            return head->data;
        }
    }

//const T& top() const:
template<typename T>
    const T& Stack<T>::top() const
    {
        if(!empty()){
            return head->data;
        }
    }

//int size() const:
template<typename T>
    int Stack<T>::size() const
    {
        return stackSize;
    }

//void print(std::ostream& os, char ofc = ' ') const:
template<typename T>
    void Stack<T>::print(std::ostream& os, char ofc) const
    {
        // Create a temporary vector
        Node* current = head;
        T* temp_vec = new T[stackSize];
        int i = stackSize - 1;

        // Shallow copy current stack to temporary vector to print in opposite order
        while (current) {
            temp_vec[i--] = current->data;
            current = current->next;
        }
        
        // Print the temporary vector
        for (i = 0; i < stackSize; ++i) {
            os << temp_vec[i];
            if (i < stackSize - 1){
                os << ofc;
            } 
        }

        // Delete temporary vector
        delete[] temp_vec;
    }

//----------------------------------------
// ====== Private helper functions =======
//----------------------------------------

//copyFrom(const Stack<T>& rhs)
template <typename T>
void Stack<T>::copyFrom(const Stack<T>& rhs) {
        // Check if other stack is empty
        if(rhs.empty()){
            return;
        }

        // Deep copy head
        Node* current = rhs.head;
        Node* tail = nullptr;
        head = new Node(current->data);
        tail = head;
        current = current->next;
        ++stackSize;

        // Iterate through other stack and deep copy into new stack
        while (current) {
            tail->next = new Node(current->data);
            tail = tail->next;
            current = current->next;
            ++stackSize;
        }
}

//----------------------------------------
// ===== Non-Member global functions =====
//----------------------------------------
//std::ostream& operator<< (std::ostream& os, const Stack<T>& a)
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    stack.print(os);
    return os;
}

//bool operator== (const Stack<T>&, const Stack <T>&)
template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    auto *node_a = a.head, *node_b = b.head;
    while (node_a && node_b) {
        if (node_a->data != node_b->data){
            return false;
        }
        node_a = node_a->next;
        node_b = node_b->next;
    }
    return true;
}

//bool operator!= (const Stack<T>&, const Stack <T>&)
template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
    return !(a == b);
}

//bool operator<=(const Stack<T>& a, const Stack <T>& b)
template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b) {
    auto *node_a = a.head, *node_b = b.head;
    while (node_a && node_b) {
        if (node_a->data > node_b->data){
            return false;
        }
        node_a = node_a->next;
        node_b = node_b->next;
    }
    return node_a == nullptr;
}


#endif