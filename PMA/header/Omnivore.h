#ifndef OMNIVORE_H_
#define OMNIVORE_H_

#include <iostream>
#include "Character.h"

using namespace std;

class Omnivore: public Character {
    public: 
        Omnivore(): Character() {
            setLetter('O');
            setMP(8);
            setHealth(10);
            setHealthMax(50);
        }
        Omnivore(int y, int x): Character(y, x) {
            setLetter('O');
            setMP(8);
            setHealth(10);
            setHealthMax(50);
        }

        void increaseHealth() override{
            Character::increaseHealth();
            if(getHealth() >= 25){
                setLetter('O');
            }
		}

		void decreaseHealth() override{
			Character::decreaseHealth();
            if(getHealth() < 25){
                setLetter('o');
            }
		}

		void decreaseOneHealth() override{
            Character::decreaseOneHealth();
            if(getHealth() < 25){
                setLetter('o');
            }
		}
};

#endif // OMNIVORE_H_
