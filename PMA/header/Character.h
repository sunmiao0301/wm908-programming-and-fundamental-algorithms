#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <iostream>
#include "Direction.h"
#include "Map.h"

using namespace std;

class Character {
    private: 
		char letter;
		int MP;
		int x;
		int y;
		int health;
		float FR;
		int healthPointsConsumed;
		int healthMax;

    public: 
		Character() {
			setLetter(' ');
			setFR(0.5);
			healthPointsConsumed = 10;
		}

		Character(int y, int x){
			setLetter(' ');
			setY(y);
			setX(x);
			setFR(0.5);
			healthPointsConsumed = 10;
		}

		char getLetter() {
			return letter;
		}

		void setLetter(char letter_) {
			letter = letter_;
		}

		int getX(){
			return x;
		}

		void setX(int x_){
			x = x_;
		}

		int getY(){
			return y;
		}

		void setY(int y_){
			y = y_;
		}

		int getMP(){
			return MP;
		}

		void setMP(int MP_){
			MP = MP_;
		}

		int getHealth(){
			return health;
		}

		void setHealth(int health_){
			health = health_;
		}

		double getFR(){
			return FR;
		}

		void setFR(float FR_){
			FR = FR_;
		}

		int getHealthPointsConsumed(){
			return healthPointsConsumed;
		}

		void setHealthPointsConsumed(int healthPointsConsumed_){
			healthPointsConsumed = healthPointsConsumed_;
		}

		int getHealthMax(){
			return healthMax;
		}

		void setHealthMax(int healthMax_){
			healthMax = healthMax_;
		}

		// 提高可读性
		// getDirection可以合并到move函数中，但是会导致多层嵌套，可读性也会降低，所以我保留了这个设计
		Direction getDirection(int MP){
			//0 UP
			//1 DOWN
			//2 LEFT
			//3 RIGHT
			if(MP == -1){// FOR Hash
				return STAY;
			}
			else if(MP == 0){
				return UP;
			}
			else if (MP == 1){
				return DOWN;
			}
			else if (MP == 2){
				return LEFT;
			}
			else if (MP == 3){
				return RIGHT;
			}
			else if (MP == 4){
				int random_num = rand() % 4;
				return getDirection(random_num);
			}
			else {
				int random_num = rand() % MP;
				if(random_num > 3){
					return STAY;
				}
				else{
					return getDirection(random_num);
				}
			}
		}

		int getNewY(Direction d){
			if(d == UP){
				return y - 1;
			}
			else if(d == DOWN){
				return y + 1;
			}
			else{
				return y;
			}
		}

		int getNewX(Direction d){
			if(d == LEFT){
				return x - 1;
			}
			else if(d == RIGHT){
				return x + 1;
			}
			else{
				return x;
			}
		}

		// if STAY, return false
		// if moved, return true
		bool move(Direction d, int X, int Y){
			if(d == UP && y - 1 >= 0){
				y--;
			}
			else if (d == DOWN && y + 1 < Y){
				y++;
			}
			else if (d == LEFT && x - 1 >= 0){
				x--;
			}
			else if (d == RIGHT && x + 1 < X){
				x++;
			}
			else {
				//STAY
				return false;
			}
			return true;
		}

		virtual void increaseHealth(){
			health += healthPointsConsumed;
			if(health > healthMax){
				health = healthMax;
			}
		}

		virtual void decreaseHealth(){
			health -= healthPointsConsumed;
			if(health < 0){
				health = 0;
			}
		}

		virtual void decreaseOneHealth(){
			health--;
			if(health < 0){
				health = 0;
			}
		}

		// Character* reproduct(){

		// }
};

#endif // CHARACTER_H