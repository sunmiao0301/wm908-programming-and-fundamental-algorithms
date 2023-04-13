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
        }
        Omnivore(int y, int x): Character(y, x) {
            setLetter('O');
            setMP(5);
            // setY(y);
			// setX(x);
        }
};

#endif // OMNIVORE_H_
