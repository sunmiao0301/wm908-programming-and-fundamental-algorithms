#ifndef CARNIVORE_H_
#define CARNIVORE_H_

#include <iostream>
#include "Character.h"

using namespace std;

class Carnivore: public Character {
    public:
        Carnivore(): Character() {
            setLetter('C');
            setMP(5);
            setHealth(50);
            setHealthMax(50);
        }

        Carnivore(int y, int x): Character(y, x) {
            setLetter('C');
            setMP(5);
            setHealth(50);
            setHealthMax(50);
        }

        void increaseHealth() override{
            Character::increaseHealth();
            if(getHealth() >= 25){
                setLetter('C');
            }
		}

		void decreaseHealth() override{
			Character::decreaseHealth();
            if(getHealth() < 25){
                setLetter('c');
            }
		}

		void decreaseOneHealth() override{
            Character::decreaseOneHealth();
            if(getHealth() < 25){
                setLetter('c');
            }
		}
};

#endif // CARNIVORE_H_



