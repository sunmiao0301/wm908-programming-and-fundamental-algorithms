#ifndef HUNTER_H_
#define HUNTER_H_

#include <iostream>
#include "Character.h"

using namespace std;

class Queue {
public:
    Queue(int capacity) {
        data_ = new int[capacity];
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        rear_ = -1;
    }

    ~Queue() {
        delete[] data_;
    }

    bool isEmpty() {
        return size_ == 0;
    }

    bool isFull() {
        return size_ == capacity_;
    }

    void enqueue(int x) {
        if (isFull()) {
            // 队列已满，不能继续入队
            return;
        }
        rear_ = (rear_ + 1) % capacity_;
        data_[rear_] = x;
        size_++;
    }

    int dequeue() {
        if (isEmpty()) {
            // 队列已空，不能继续出队
            return -1;
        }
        int x = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        return x;
    }

private:
    int* data_;
    int capacity_;
    int size_;
    int front_;
    int rear_;
};
