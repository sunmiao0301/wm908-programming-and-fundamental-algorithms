#ifndef VEGETATION_H_
#define VEGETATION_H_

#include <iostream>
#include "Character.h"

using namespace std;

class Vegetation: public Character {
    public: 
    Vegetation(): Character() {
        setLetter('T');
        setMP(-1);
        setHealth(100);
        setHealthMax(100);
    }
    Vegetation(int y, int x): Character(y, x) {
        setLetter('T');
        setMP(-1);
        setHealth(100);
        setHealthMax(100);
    }

    void increaseHealth() override{
        Character::increaseHealth();
        if(getHealth() >= 0 && getHealth() < 33){
            setLetter('\'');
        }
        else if(getHealth() >= 33 && getHealth() < 66){
            setLetter('t');
        }
        else if(getHealth() >= 66 && getHealth() <= 100){
            setLetter('T');
        }   
    }

    void decreaseHealth() override{
        Character::decreaseHealth();
        if(getHealth() >= 0 && getHealth() < 33){
            setLetter('\'');
        }
        else if(getHealth() >= 33 && getHealth() < 66){
            setLetter('t');
        }
        else if(getHealth() >= 66 && getHealth() <= 100){
            setLetter('T');
        }   
    }

    void decreaseOneHealth() override{
        // T does not decrease over time
        // Character::decreaseOneHealth();
        if(getHealth() >= 0 && getHealth() < 33){
            setLetter('\'');
        }
        else if(getHealth() >= 33 && getHealth() < 66){
            setLetter('t');
        }
        else if(getHealth() >= 66 && getHealth() <= 100){
            setLetter('T');
        }   
    }
};

#endif // VEGETATION_H_