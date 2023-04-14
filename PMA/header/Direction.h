#ifndef DIRECTION_H_
#define DIRECTION_H_

#include <iostream>

using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STAY
};

class DirectionUtil {
public:
    static string toString(Direction dir) {
        switch (dir) {
            case UP:
                return "UP";
            case DOWN:
                return "DOWN";
            case LEFT:
                return "LEFT";
            case RIGHT:
                return "RIGHT";
            case STAY:
                return "STAY";
            default:
                return "UNKNOWN";
        }
    }
};

#endif // DIRECTION_H
