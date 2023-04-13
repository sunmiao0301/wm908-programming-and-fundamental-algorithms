#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "Character.h"
#include "Hash.h"

using namespace std;

//Map可以只用于渲染，即只存储int值就可，但是考虑到Question one and two的时候还没有容器类，所以就保留这个设计了
class Map {
    public: 
        Map(int Y_, int X_) {
            Y = Y_;
            X = X_;
            map = new Character** [Y];
            for (int i = 0; i < Y; i++) {
                map[i] = new Character* [X];
                for (int j = 0; j < X; j++) {
                    map[i][j] = new Character(); // 初始化为指向新分配的 Character 对象的指针
                }
                // map[i] = new Character[X];
                // for (int j = 0; j < X; j++) {
                //     map[i][j] = Character(); // 给每个元素赋初值为' '
                // }
            }
        }

        ~Map() {
        // 释放所有Character指针
            for (int i = 0; i < Y; i++) {
                for (int j = 0; j < X; j++) {
                    delete map[i][j];
                }
                delete[] map[i];
            }
            delete[] map;
        }

        int getY() {
            return Y;
        }

        int getX() {
            return X;
        }

        bool place(int y, int x, Character* characterPtr) {
            if (y < 0 || y >= Y || x < 0 || x >= X) {
                return false;
            }
            if (map[y][x]->getLetter() != ' ') {
                return false;
            }
            map[y][x] = characterPtr;
            return true;
        }

        //getCharXY
        char getXY(int y, int x) {
            if (y < 0 || y >= Y || x < 0 || x >= X) {
                return 'E';
            }
            return map[y][x]->getLetter();
        }

        
        Character* getCharacterXY(int y, int x){
            if (y < 0 || y >= Y || x < 0 || x >= X) {
                //因为初始都是new Character(),所以如果返回nullptr说明超界
                return nullptr;
            }
            return map[y][x];
        }

        void display() {
            // 输出地图最上面的一条横线
            for (int i = 0; i < X; ++i) {
                cout << "- - - - ";
            }
            cout << endl;

            // 输出每一行的竖线和内容
            for (int i = 0; i < Y; ++i) {
                for (int j = 0; j < X; ++j) {
                    cout << "| ";
                    // if(map[i][j].getLetter() == ' '){

                    // }
                    // cout << "      ";
                    // // cout << "  " << '#' << "   ";
                    cout << "  " << getXY(i, j) << "   ";
                }
                cout << "|" << endl;
                // 输出每行下面的一条横线
                for (int i = 0; i < X; ++i) {
                    cout << "- - - - ";
                }
                cout << endl;
            }
        }

        void addHash(int num) {// in question two, num is Y
            for (int i = 0; i < num; i++) {
                int x = rand() % X;
                int y = rand() % Y;
                if (!place(x, y, new Hash())) {
                    i--;
                }
            }
        }

    private:
        // Y refers to number of rows and is always presented first, 
        // X refers to number of columns
        int Y;
        int X;
        Character*** map;
};

#endif // MAP_H_