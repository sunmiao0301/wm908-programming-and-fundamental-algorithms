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
        //为了存储出生的新生物
        Container* containerTemp;
        int runCount;
        int vegetationNum;
        int herbivoreNum;
        int omnivoreNum;
        int carnivoreNum;
        
        Simulation(int y, int x){
            map = new Map(y, x);
            container = new Container();
            containerTemp = new Container();
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
                    }
                    container->add(herbivorePtr);
                    herbivoreNum++;
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
                while (cur != NULL) {
                    int xOld = cur->data->getX();
                    int yOld = cur->data->getY();

                    if(cur->data->getLetter() == '#'){
                        cur = cur->next;
                        continue;
                    }
                    
                    Direction d = cur->data->getDirection(cur->data->getMP());
                    int xNew = cur->data->getNewX(d);
                    int yNew = cur->data->getNewY(d);

                    //因为在我的设计中，（移动和吃） 与 繁殖是并列关系，这会导致设计难度上升
                    int yForProduct = yOld;
                    int xForProduct = xOld;

                    //decreaseOneHealth()发生的前提条件：1.移动了 2.没移动也没进食
                    //判断是否死亡而消失：1.移动了 2.被吃了一口 3.没移动也没进食
                    //通过Map的方法判断要去的位置是否 是空位,如果是，就移动。如果不是，就不移动
                    if(map->moveCharacter(yOld, xOld, yNew, xNew)){
                        cout << cur->data->getLetter() << " Move from " << "(" << yOld << ", " << xOld << ") to" << "(" << yNew << ", " << xNew << ") ";
                        cout << "The health is " << map->getCharacterXY(yNew, xNew)->getHealth() << endl;
                        //根据最新情况刷新Map和container
                        //如果确实移动了，就要判断移动后的Character会不会因为没进食饿死
                        if(map->removeCharacter(yNew, xNew)){
                            characterCountDecrease(map->getCharacterXY(yNew, xNew));
                            container->remove(map->getCharacterXY(yNew, xNew));
                            map->remove(yNew, xNew);
                            cout << "someone hungry to die after moving" << endl;
                            cur = cur->next;
                            continue;
                        }
                        //如果移动了，就要把用于繁殖的坐标(yForProduct, xForProduct)从(yOld, xOld)变换为(yNew, xNew)
                        yForProduct = yNew;
                        xForProduct = xNew;
                    }
                    else{
                        //通过Map的方法判断要去的地方能不能吃,返回false代表STAY
                        if(map->consumeCharacter(yOld, xOld, yNew, xNew)){
                            cout << cur->data->getLetter() << " Consume from " << "(" << yOld << ", " << xOld << ") to" << "(" << yNew << ", " << xNew << ") ";
                            cout << "The health of Stronger " << cur->data->getLetter() << " is " << cur->data->getHealth() ;
                            cout << " The health of Weaker " << map->getCharacterXY(yNew, xNew)->getLetter() << " is " << map->getCharacterXY(yNew, xNew)->getHealth() << endl;
                            //根据最新情况刷新Map和container
                            if(map->removeCharacter(yNew, xNew)){
                                characterCountDecrease(map->getCharacterXY(yNew, xNew));
                                container->remove(map->getCharacterXY(yNew, xNew));
                                map->remove(yNew, xNew);
                                cout << "someone hungry to die after being eaten" << endl;
                                cur = cur->next;
                                continue;
                            }
                        }
                        else{
                            cur->data->decreaseOneHealth();
                            cout << cur->data->getLetter() << " STAY at " << "(" << yOld << ", " << xOld << ") ";
                            cout << "The health is " << map->getCharacterXY(yOld, xOld)->getHealth() << endl;
                            if(map->removeCharacter(yOld, xOld)){
                                characterCountDecrease(cur->data);
                                container->remove(cur->data);
                                map->remove(yOld, xOld);
                                cout << "someone hungry to die without moving and being eaten" << endl;
                                cur = cur->next;
                                continue;
                            }
                        }
                    }

                    //如果移动和吃 部分完成后还没饿死，就进行繁殖

                    //繁殖 繁殖这一部分代码，有点过分冗余，但是这段细节太多，不敢重构了。
                    float randomValue = static_cast<float>(rand()) / RAND_MAX;
                    if (randomValue < cur->data->getFR()) {
                        // for(int i = 0; i < 4; i++){
                            //因为繁殖不包括STAY，所以要重新设计
                            Direction* directions = new Direction[4];
                            int count = 0;
                            if (map->getXY(yForProduct - 1, xForProduct) == ' ') {
                                directions[count] = UP;
                                count++;
                            }
                            if (map->getXY(yForProduct + 1, xForProduct) == ' ') {
                                directions[count] = DOWN;
                                count++;
                            }
                            if (map->getXY(yForProduct, xForProduct - 1) == ' ') {
                                directions[count] = LEFT;
                                count++;
                            }
                            if (map->getXY(yForProduct, xForProduct + 1) == ' ') {
                                directions[count] = RIGHT;
                                count++;
                            }
                            
                            if (count > 0) {
                                int randomIndex = rand() % count;
                                Direction randomDirection = directions[randomIndex];
                                // map->reproduceCharacter();
                                if(dynamic_cast<Carnivore*>(cur->data)){
                                    Character* carnivore = new Carnivore(cur->data->getNewY(randomDirection), cur->data->getNewX(randomDirection));
                                    map->place(cur->data->getNewY(randomDirection), cur->data->getNewX(randomDirection), carnivore);
                                    containerTemp->add(carnivore);
                                    carnivoreNum++;
                                    cout << "and reproduce at direction " << DirectionUtil::toString(randomDirection) << endl;
                                }
                                else if (dynamic_cast<Herbivore*>(cur->data))
                                {
                                    
                                    Character* herbivore = new Herbivore(cur->data->getNewY(randomDirection), cur->data->getNewX(randomDirection));
                                    // cout << herbivore->getMP();
                                    map->place(cur->data->getNewY(randomDirection), cur->data->getNewX(randomDirection), herbivore);
                                    containerTemp->add(herbivore);
                                    // containerTemp->print();
                                    herbivoreNum++;
                                    cout << "and reproduce at direction " << DirectionUtil::toString(randomDirection) << endl;
                                }
                                else if (dynamic_cast<Omnivore*>(cur->data))
                                {
                                    Character* omnivore = new Omnivore(cur->data->getNewY(randomDirection), cur->data->getNewX(randomDirection));
                                    map->place(cur->data->getNewY(randomDirection), cur->data->getNewX(randomDirection), omnivore);
                                    containerTemp->add(omnivore);
                                    omnivoreNum++;
                                    cout << "and reproduce at direction " << DirectionUtil::toString(randomDirection) << endl;
                                }
                                else if (dynamic_cast<Vegetation*>(cur->data))
                                {
                                    Character* vegetation = new Vegetation(cur->data->getNewY(randomDirection), cur->data->getNewX(randomDirection));
                                    map->place(cur->data->getNewY(randomDirection), cur->data->getNewX(randomDirection), vegetation);
                                    containerTemp->add(vegetation);
                                    vegetationNum++;
                                    cout << "and reproduce at direction " << DirectionUtil::toString(randomDirection) << endl;
                                }
                        }
                    }
                    cur = cur->next;
                }

                // 将 containerTemp 中存放的 Character 对象移动到主 container 中
                Container::Node* curTemp = containerTemp->getHead();
                while (curTemp != nullptr) {
                    container->add(curTemp->data);
                    curTemp = curTemp->next;
                }
                containerTemp->clearButKeepData();

                map->display();
                container->print();
                cout << "Step: " << runCount << " T: " << vegetationNum << " H: " << herbivoreNum << " C: " << carnivoreNum << " O: " << omnivoreNum << endl;
                runCount++;
            }
        }

        void characterCountDecrease(Character * c){
            if(c->getLetter() == 'T' || c->getLetter() == 't' || c->getLetter() == '\''){
                vegetationNum--;
            }
            else if (c->getLetter() == 'H' || c->getLetter() == 'h'){
                herbivoreNum--;
            }
            else if (c->getLetter() == 'O' || c->getLetter() == 'o'){
                omnivoreNum--;
            }
            else if (c->getLetter() == 'C' || c->getLetter() == 'c'){
                carnivoreNum--;
            }
            else{//for R hunter

            }
        }

        // 释放内存
        void free(){
            Container::Node* cur = container->getHead();
            while (cur != NULL) {
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