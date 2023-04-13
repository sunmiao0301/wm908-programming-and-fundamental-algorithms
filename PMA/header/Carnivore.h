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
        }

        Carnivore(int y, int x): Character(y, x) {
            setLetter('C');
            setMP(5);
            // setY(y);
			// setX(x);
        }
};

#endif // CARNIVORE_H_



