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
        }
};

#endif // HERBIVORE_H_
