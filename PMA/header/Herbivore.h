#ifndef HERBIVORE_H_
#define HERBIVORE_H_

#include <iostream>
#include "Character.h"

using namespace std;

class Herbivore: public Character {
    public: 
        Herbivore(): Character() {
            setLetter('H');
            setMP(5);
            setHealth(50);
            setHealthMax(50);
        }
        Herbivore(int y, int x): Character(y, x) {
            setLetter('H');
            setMP(5);
            setHealth(50);
            setHealthMax(50);
        }
        
        void increaseHealth() override{
            Character::increaseHealth();
            if(getHealth() >= 25){
                setLetter('H');
            }
		}

		void decreaseHealth() override{
			Character::decreaseHealth();
            if(getHealth() < 25){
                setLetter('h');
            }
		}

		void decreaseOneHealth() override{
            Character::decreaseOneHealth();
            if(getHealth() < 25){
                setLetter('h');
            }
		}
};

#endif // HERBIVORE_H_
