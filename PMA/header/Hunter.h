#ifndef HUNTER_H_
#define HUNTER_H_

#include <iostream>
#include "Character.h"

using namespace std;

class Hunter: public Character {
    public:
        Hunter(): Character() {
            setLetter('R');
            setMP(5);
            setHealth(50);
            setHealthMax(50);
        }

        Hunter(int y, int x): Character(y, x) {
            setLetter('R');
            setMP(5);
            setHealth(50);
            setHealthMax(50);
        }

        void increaseHealth() override{
            Character::increaseHealth();
            if(getHealth() >= 25){
                setLetter('R');
            }
		}

		void decreaseHealth() override{
			Character::decreaseHealth();
            if(getHealth() < 25){
                setLetter('r');
            }
		}

		void decreaseOneHealth() override{
            Character::decreaseOneHealth();
            if(getHealth() < 25){
                setLetter('r');
            }
		}
};

#endif // HUNTER_H_