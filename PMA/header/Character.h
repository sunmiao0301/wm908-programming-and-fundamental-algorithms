#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <iostream>
#include "Direction.h"

using namespace std;

class Character {
    private: 
		char letter;
		int MP;
		int x;
		int y;

    public: 
		Character() {
			setLetter(' ');
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

		// 提高可读性
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

};

#endif // CHARACTER_H