#include "../header/Map.h"
#include "../header/Character.h"
#include "../header/Vegetation.h"
#include "../header/Herbivore.h"
#include "../header/Omnivore.h"
#include "../header/Carnivore.h"
#include "../header/Hash.h"
#include "../header/Container.h"
#include "../header/Direction.h"
#include "../header/Simulation.h"

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


void questionThree() {
	// ii)
	Simulation* simulation = new Simulation(7, 10);

	simulation->initCharacter(12, '#');
	simulation->initCharacter(3, 'T');
	simulation->initCharacter(3, 'H');
	simulation->initCharacter(3, 'O');
	simulation->initCharacter(3, 'C');

	simulation->map->display();
	simulation->container->print();

	// iii)
	simulation->run(3);

	
}


int main() {
    srand(time(NULL));
    // questionTwo();
    questionThree();
    return 0;
}