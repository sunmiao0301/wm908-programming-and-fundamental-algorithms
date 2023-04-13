#ifndef VEGETATION_H_
#define VEGETATION_H_

#include <iostream>
#include "Character.h"

using namespace std;

class Vegetation: public Character {
    public: 
    Vegetation(): Character() {
        setLetter('T');
        setMP(0);
    }
    Vegetation(int y, int x): Character(y, x) {
        setLetter('T');
        setMP(5);
        // setY(y);
        // setX(x);
    }
};

#endif // VEGETATION_H_