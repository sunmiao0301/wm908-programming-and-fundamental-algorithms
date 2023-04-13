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
};

#endif // VEGETATION_H_