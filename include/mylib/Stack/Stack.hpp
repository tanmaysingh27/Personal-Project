#pragma once

#include <iostream>
#include <stdexcept>

namespace myLib {

    template <typename T>
    class Stack {
    private:
        T* data;
        int capacity;
        int top;

        void resize(int newCapacity);

    public:
        Stack(int cap) : capacity(cap), top(-1) {
            data = new T[capacity];
        }

        ~Stack() {
            delete[] data;
        }

        //! Copy constructor — deep copy
        Stack(const Stack& other) : capacity(other.capacity), top(other.top) {
            data = new T[capacity];
            for (int i = 0; i <= top; i++) {
                data[i] = other.data[i];
            }
        }

        //! Copy assignment — deep copy with self-check
        Stack& operator=(const Stack& other) {
            if (this == &other) return *this;

            delete[] data;

            capacity = other.capacity;
            top = other.top;
            data = new T[capacity];
            for (int i = 0; i <= top; i++) {
                data[i] = other.data[i];
            }

            return *this;
        }

        void push(T value);
        T pop();
        T peek() const;
        bool isEmpty() const;
        bool isFull() const;
    };

    //! Stack methods

    template <typename T>
    void Stack<T>::resize(int newCapacity) {
        T* newData = new T[newCapacity];

        for (int i = 0; i <= top; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    template <typename T>
    void Stack<T>::push(T value) {
        if (isFull()) {
            resize((capacity == 0) ? 1 : capacity * 2);
        }
        data[++top] = value;
    }

    template <typename T>
    T Stack<T>::pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty: cannot pop");
        }
        return data[top--];
    }

    template <typename T>
    T Stack<T>::peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty: nothing to peek");
        }
        return data[top];
    }

    template <typename T>
    bool Stack<T>::isEmpty() const {
        if (top == -1) {
            return true;
        }
        else {
            return false;
        }
    }

    template <typename T>
    bool Stack<T>::isFull() const {
        if (top == capacity - 1) {
            return true;
        }
        else {
            return false;
        }
    }

} // namespace myLib