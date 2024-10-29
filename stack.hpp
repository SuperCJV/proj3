#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "stack.h"

//----------------------------------------
// =========== Member functions ==========
//----------------------------------------

//Stack():
template<typename T>
    Stack<T>::Stack()
    {
            stackSize = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
    }

//~Stack ():
template<typename T>
    Stack<T>::~Stack()
    {
        clear();

        delete head;
        delete tail;
    }

//Stack (const Stack<T>&):
//template<typename T>

//Stack(Stack<T> &&):
//template<typename T>

//Stack<T>& operator= (const Stack <T>&):
//template<typename T>

//Stack<T> & operator=(Stack<T> &&):
//template<typename T>

//bool empty() const:
template<typename T>
    bool Stack<T>::empty() const{
        return theSize==;
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
//template<typename T>

//void push(T && x):
//template<typename T>

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
//template<typename T>

//const T& top() const:
//template<typename T>

//int size() const:
//template<typename T>

//void print(std::ostream& os, char ofc = ' ') const:
//template<typename T>

//----------------------------------------
// ===== Non-Member global functions =====
//----------------------------------------

#endif