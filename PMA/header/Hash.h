#ifndef HASH_H_
#define HASH_H_

#include <iostream>

#include "Character.h"

using namespace std;

class Hash: public Character {
    public: 
        Hash(): Character() {
            setLetter('#');
            setMP(-1);
        }
};

#endif // HASH_H_