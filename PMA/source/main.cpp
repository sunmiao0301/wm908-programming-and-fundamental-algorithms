#include "../header/Map.h"
#include "../header/Character.h"
#include "../header/Vegetation.h"
#include "../header/Herbivore.h"
#include "../header/Omnivore.h"
#include "../header/Carnivore.h"
#include "../header/Hash.h"
#include "../header/Container.h"

using namespace std;

void questionTwo() {
    // 初始化一个7x10的地图
    Map map(7, 10);

    // ii) 
    cout << "Did map.place() work?" << boolalpha << map.place(7, 9, new Vegetation()) << endl;
    cout << "Did map.place() work?" << boolalpha << map.place(6, 9, new Vegetation()) << endl;
    cout << "Did map.place() work?" << boolalpha << map.place(6, 9, new Vegetation()) << endl;
    cout << "Did map.getXY() work?" << map.getXY(7, 9) << endl;
    cout << "Did map.getXY() work?" << map.getXY(6, 9) << endl;

    // iii) 通过map::display()提供显示地图的功能
    map.display();

    // iv) 
    srand(time(NULL)); // 初始化随机数种子
    for (int i = 0; i < 15; i++) {
        int x = rand() % map.getX();
        int y = rand() % map.getY();
        if (!map.place(y, x, new Hash())) {
            i--;
        }
    }
    map.display();
    cout << "Did map.place() work?" << boolalpha << map.place(7, 9, new Hash()) << endl;
    cout << "Did map.place() work?" << boolalpha << map.place(6, 9, new Hash()) << endl;

    // v)
    Map mapSmall(1, 1);
    mapSmall.addHash(1);
    mapSmall.display();

    Map mapMedium(7, 10);
    mapMedium.addHash(7);
    mapMedium.display();

    Map mapBig(15, 20);
    mapBig.addHash(15);
    mapBig.display();
	//Remember delete and free storage
}

void initCharacter(int num, char flag, Map* map, Container* container){
	// for(int i = 0; i < num; i++){
	// Use while but for loop to make continue meaningful and without i--;
	int i = 0;
	while(i < num){
		int x = rand() % map->getX();
		int y = rand() % map->getY();
		if(flag == '#'){
			Character* hashPtr = new Hash();
			if (!map->place(y, x, hashPtr)) {
				continue;
			}
			// 如果用这种写法：container->add(vegetationPtr);
			// 需要使用箭头运算符来调用指向对象的指针的方法
			container->add(hashPtr);
		}
		else if (flag == 'T'){
			Character* vegetationPtr = new Vegetation();
			if (!map->place(y, x, vegetationPtr)) {
				continue;
			}
			container->add(vegetationPtr);
		}
		else if (flag == 'H'){
			Character* herbivorePtr = new Herbivore();
			if (!map->place(y, x, herbivorePtr)) {
				continue;
			}
			container->add(herbivorePtr);
		}
		else if (flag == 'O'){
			Character* omnivorePtr = new Omnivore();
			if (!map->place(y, x, omnivorePtr)) {
				continue;
			}
			container->add(omnivorePtr);
		}
		else if (flag == 'C')
		{
			Character* carnivorePtr = new Carnivore();
			if (!map->place(y, x, carnivorePtr)) {
				continue;
			}
			container->add(carnivorePtr);
		}
		// else{
		// 	//Hunter
		// }
		i++;
	}
	
}

void questionThree() {
	// ii)
	Map* mapPtr = new Map(7, 10);
	Container* containerPtr = new Container();

	initCharacter(12, '#', mapPtr, containerPtr);
	initCharacter(3, 'T', mapPtr, containerPtr);
	initCharacter(3, 'H', mapPtr, containerPtr);
	initCharacter(3, 'O', mapPtr, containerPtr);
	initCharacter(3, 'C', mapPtr, containerPtr);

	mapPtr->display();
	containerPtr->print();

	// iii)
	for(int i = 0; i < 3; i++){
		Container::Node* cur = containerPtr->getHead();
		while (cur != nullptr) {
			if(cur->data->move(cur->data->getDirection(cur->data->getMP()), mapPtr->getX(), mapPtr->getY())){
				// mapPtr->getXY(mapPtr->getX(), mapPtr->getY())/////////////////
			}
			cur = cur->next;
		}
		mapPtr->display();
	}

    // 释放内存
	Container::Node* cur = containerPtr->getHead();
	while (cur != nullptr) {
		Container::Node* next = cur->next;
		delete cur->data;
		delete cur;
		cur = next;
	}
    delete containerPtr;
    delete mapPtr;
}


int main() {
    srand(time(NULL));
    // questionTwo();
    questionThree();
    return 0;
}