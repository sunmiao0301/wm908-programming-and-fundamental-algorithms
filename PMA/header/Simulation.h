#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include "Map.h"
#include "Character.h"
#include "Vegetation.h"
#include "Herbivore.h"
#include "Omnivore.h"
#include "Carnivore.h"
#include "Hash.h"
#include "Container.h"
#include "Direction.h"

using namespace std;

class Simulation {
    public: 
        Map* map;
        Container* container;
        int runCount;
        int vegetationNum;
        int herbivoreNum;
        int omnivoreNum;
        int carnivoreNum;
        
        Simulation(int y, int x){
            map = new Map(y, x);
            container = new Container();
            runCount = 0;
            vegetationNum = 0;
            herbivoreNum = 0;
            omnivoreNum = 0;
            carnivoreNum = 0;
        }

        void initCharacter(int num, char flag){
            // for(int i = 0; i < num; i++){
            // Use while but for loop to make continue meaningful and without i--;
            int i = 0;
            while(i < num){
                int x = rand() % map->getX();
                int y = rand() % map->getY();
                if(flag == '#'){
                    Character* hashPtr = new Hash(y, x);
                    if (!map->place(y, x, hashPtr)) {
                        continue;
                    }
                    // 如果用这种写法：container->add(vegetationPtr);
                    // 需要使用箭头运算符来调用指向对象的指针的方法
                    container->add(hashPtr);
                }
                else if (flag == 'T'){
                    Character* vegetationPtr = new Vegetation(y, x);
                    if (!map->place(y, x, vegetationPtr)) {
                        continue;
                    }
                    container->add(vegetationPtr);
                    vegetationNum++;
                }
                else if (flag == 'H'){
                    Character* herbivorePtr = new Herbivore(y, x);
                    if (!map->place(y, x, herbivorePtr)) {
                        continue;
                        herbivoreNum++;
                    }
                    container->add(herbivorePtr);
                }
                else if (flag == 'O'){
                    Character* omnivorePtr = new Omnivore(y, x);
                    if (!map->place(y, x, omnivorePtr)) {
                        continue;
                    }
                    container->add(omnivorePtr);
                    omnivoreNum++;
                }
                else if (flag == 'C')
                {
                    Character* carnivorePtr = new Carnivore(y, x);
                    if (!map->place(y, x, carnivorePtr)) {
                        continue;
                    }
                    container->add(carnivorePtr);
                    carnivoreNum++;
                }
                // else{
                // 	//Hunter
                // }
                i++;
            }
        }

        void run(int steps){
            while(runCount < steps){
                Container::Node* cur = container->getHead();
                while (cur != nullptr) {
                    int xOld = cur->data->getX();
                    int yOld = cur->data->getY();
                    Direction d = cur->data->getDirection(cur->data->getMP());

                    int xNew = cur->data->getNewX(d);
                    int yNew = cur->data->getNewY(d);

                    //判断要去的位置是否是空位
                    if(map->reachableAt(yNew, xNew)){
                        map->moveCharacter(yOld, xOld, d);
                        // cout << cur->data->getLetter() << "Move from " << "(" << yOld << ", " << xOld << ") to" << "(" << yNew << ", " << xNew << ")" << endl;
                    }
                    cur = cur->next;
                }
                map->display();
                cout << "Step: " << runCount << " T: " << vegetationNum << " H: " << herbivoreNum << " C: " << carnivoreNum << " O: " << omnivoreNum << endl;
                runCount++;
            }
        }

        // 释放内存
        void free(){
            Container::Node* cur = container->getHead();
            while (cur != nullptr) {
                Container::Node* next = cur->next;
                delete cur->data;
                delete cur;
                cur = next;
            }
            delete container;
            delete map;
        }
};

#endif // SIMULATION_H_