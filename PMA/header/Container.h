#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <iostream>
#include "Character.h"

using namespace std;

class Container {
    public:
    struct Node {
            Character* data;
            Node* next;
        };
    private:
        Node* head;
        int size;

    public:
        
        Container() {
            head = nullptr;
            size = 0;
        }

        // 为了释放内存
        Node* getHead() {
            return head;
        }

        // void add(Character* c) {
        //     Node* node = new Node();
        //     node->data = c;
        //     node->next = head;
        //     head = node;
        // }

        int getSize(){
            return size;
        }

        void add(Character* c) {
            Node* node = new Node();
            node->data = c;
            node->next = nullptr;
            if (head == nullptr) {
                head = node;
            } else {
                Node* tail = head;
                while (tail->next != nullptr) {
                    tail = tail->next;
                }
                tail->next = node;
            }
            size++;
        }

        void remove(Character* c) {
            Node* prev = nullptr;
            Node* cur = head;
            while (cur != nullptr && cur->data != c) {
                prev = cur;
                cur = cur->next;
            }
            if (cur == nullptr) {
                return;
            }
            if (prev == nullptr) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            size--;
        }

        void clear() {
            Node* cur = head;
            while (cur != nullptr) {
                Node* next = cur->next;
                delete cur->data;
                delete cur;
                cur = next;
            }
            size = 0; // 重置容器大小
            head = nullptr;
        }

        void clearButKeepData () {
            Node* cur = head;
            while (cur != nullptr) {
                Node* next = cur->next;
                cur->next = nullptr; // 防止在删除节点时也删除其它节点
                cur = next;
            }
            size = 0; // 重置容器大小
            head = nullptr; // 清空容器
        }


        void print() {
            Node* cur = head;
            while (cur != nullptr) {
                cout << cur->data->getLetter() << " ";
                cur = cur->next;
            }
            cout << endl;
        }

};

#endif // CONTAINER_H_
