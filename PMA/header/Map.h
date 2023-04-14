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

        //place 代表在一定条件下，在map数据结构中(y, x)位置上放入characterPtr
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
                if (!place(y, x, new Hash())) {
                    i--;
                }
            }
        }

        bool moveCharacter(int yOld, int xOld, int yNew, int xNew){
           if(getXY(yNew, xNew) != ' '){
                return false;
            }
            getCharacterXY(yOld, xOld)->decreaseOneHealth();

            // cout << "The des is " << getXY(yNew, xNew) << ". "  ;

            Character* ch = map[yOld][xOld];
            map[yOld][xOld] = new Character();
            map[yNew][xNew] = ch;
            ch->setY(yNew);
            ch->setX(xNew);
            return true;
        }
        
        char uppercase(char c){
            if(c == 'h'){
                return 'H';
            }
            if(c == 'c'){
                return 'C';
            }
            if(c == 'o'){
                return 'O';
            }
            if(c == 't' || c == '\''){
                return 'T';
            }
            return c;
        }

        bool consumeCharacter(int yOld, int xOld, int yNew, int xNew){
            //随机的方向超界
            if(getXY(yNew, xNew) == 'E'){
                // getCharacterXY(yOld, xOld)->decreaseOneHealth();
                return false;
            }

            //自己不能吃自己（当该Character选择不动的时候）
            if(yOld == yNew && xOld == xNew){
                // getCharacterXY(yOld, xOld)->decreaseOneHealth();
                return false;
            }

            char src = uppercase(getXY(yOld, xOld));
            char des = uppercase(getXY(yNew, xNew));

            //使用return是因为如果发生了consume，srcCharacter就不需要decreaseOneHealth()
            if(src == '#' || des == '#'){
                return false;
            }

            if(src == 'H' && des == 'T'){
                getCharacterXY(yOld, xOld)->increaseHealth();
                getCharacterXY(yNew, xNew)->decreaseHealth();
                // cout << "The des is " << getXY(yNew, xNew) << ". "  ;
                return true;
            }

            if(src == 'C' && des == 'H'){
                getCharacterXY(yOld, xOld)->increaseHealth();
                getCharacterXY(yNew, xNew)->decreaseHealth();
                // cout << "The des is " << getXY(yNew, xNew) << ". "  ;
                return true;
            }

            if(src == 'O' && (des == 'T' || des == 'H')){
                getCharacterXY(yOld, xOld)->increaseHealth();
                getCharacterXY(yNew, xNew)->decreaseHealth();
                // cout << "The des is " << getXY(yNew, xNew) << ". "  ;
                return true;
            }
    
            // getCharacterXY(yOld, xOld)->decreaseOneHealth();
            return false;
        }

        // remove 代表从map数据结构中删除(y, x)位置上的Character
        void remove(int y, int x){
            map[y][x] = new Character();
        }

        bool removeCharacter(int y, int x){
            if(getCharacterXY(y, x)->getHealth() == 0){
                // Character* ch = map[y][x];
                // map[y][x] = new Character();
                return true;
            }
            return false;
        }

        // void reproduceCharacter(){

        // }



    private:
        // Y refers to number of rows and is always presented first, 
        // X refers to number of columns
        int Y;
        int X;
        Character*** map;
};

#endif // MAP_H_