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

void questionFour() {

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
	simulation->run(20);
}

void questionFiveOne(){
	Simulation* simulation = new Simulation(14, 14);
	simulation->initCharacter(12, '#');
	simulation->initCharacter(20, 'T');
	simulation->initCharacter(20, 'H');
	simulation->initCharacter(0, 'O');
	simulation->initCharacter(0, 'C');

	// simulation->map->display();
	// simulation->container->print();

	// iii)
	simulation->run(50);
}


void questionFiveTwo(){

    Simulation* simulation = new Simulation(14, 14);
	simulation->initCharacter(12, '#');
	simulation->initCharacter(20, 'T');
	simulation->initCharacter(20, 'H');
	simulation->initCharacter(0, 'O');
	simulation->initCharacter(20, 'C');
    
    char input;
    while (true) {
        // cout << "Press 'q' to quit, or any other key to continue: ";
        input = cin.get();
        cin.ignore(256, '\n'); // 忽略缓冲区中的回车键
        if (input == 'q') {
            break;
        }
        simulation->run();
    }
}

void questionFiveThree(){
    Simulation* simulation = new Simulation(14, 14);
	simulation->initCharacter(12, '#');
	simulation->initCharacter(20, 'T');
	simulation->initCharacter(20, 'H');
	simulation->initCharacter(0, 'O');
	simulation->initCharacter(20, 'C');
    
    char input;
    while (true) {
        // cout << "Press 'q' to quit, or any other key to continue: ";
        input = cin.get();
        cin.ignore(256, '\n'); // 忽略缓冲区中的回车键
        if (input == 'q') {
            break;
        }
        simulation->run();
    }
}

void questionFiveFour(){
	// simulation->map->display();
	// simulation->container->print();
    Simulation* simulation = new Simulation(14, 14);
    simulation->initCharacter(12, '#');
    simulation->initCharacter(20, 'T');
    simulation->initCharacter(20, 'H');
    simulation->initCharacter(0, 'O');
    simulation->initCharacter(20, 'C');
    simulation->run(1000);
}

void questionFiveFive(){
    int vegetationSum = 0;
    int herbivoreSum = 0;
    int omnivoreSum = 0;
    int carnivoreSum = 0;
    for(int i = 0; i < 100; i++){
        Simulation* simulation = new Simulation(14, 14);
	    simulation->initCharacter(12, '#');
	    simulation->initCharacter(20, 'T');
	    simulation->initCharacter(20, 'H');
	    simulation->initCharacter(0, 'O');
	    simulation->initCharacter(20, 'C');
        simulation->run(5000);
        vegetationSum += simulation->vegetationNum;
        herbivoreSum += simulation->herbivoreNum;
        omnivoreSum += simulation->omnivoreNum;
        carnivoreSum += simulation->carnivoreNum;

        // delete simulation;
    }
    cout << "Average " << " T: " << vegetationSum / 100 << " H: " << herbivoreSum / 100 << " C: " << carnivoreSum / 100 << " O: " << omnivoreSum / 100 << endl;
}

void questionFiveSix(){
    int vegetationSum = 0;
    int herbivoreSum = 0;
    int omnivoreSum = 0;
    int carnivoreSum = 0;
    for(int i = 0; i < 100; i++){
        Simulation* simulation = new Simulation(14, 14);
	    simulation->initCharacter(12, '#');
	    simulation->initCharacter(20, 'T');
	    simulation->initCharacter(20, 'H');
	    simulation->initCharacter(10, 'O');
	    simulation->initCharacter(20, 'C');
        simulation->run(5000);
        vegetationSum += simulation->vegetationNum;
        herbivoreSum += simulation->herbivoreNum;
        omnivoreSum += simulation->omnivoreNum;
        carnivoreSum += simulation->carnivoreNum;

        // delete simulation;
    }
    cout << "Average " << " T: " << vegetationSum / 100 << " H: " << herbivoreSum / 100 << " C: " << carnivoreSum / 100 << " O: " << omnivoreSum / 100 << endl;
}


/**
 * Question 6 i)
 * 我运行并且在控制台输出了每Character的血量和活动情况，我发现：
 * Q5 iv
 * （这里可以画一个拟合图）
 * step = 5，Average  T: 23 H: 23 C: 22 O: 0   ----  大家数量都差不多
 * step = 40，Average  T: 44 H: 28 C: 53 O: 0  ----  T和C开始上升 H下降
 * step = 100, Average  T: 64 H: 11 C: 75 O: 0  ----  T和C持续上升，H继续下降
 * step = 200, Average  T: 110 H: 4 C: 47 O: 0
 * step = 500, Average  T: 171 H: 4 C: 4 O: 0
 * step = 1000, Average  T: 157 H: 17 C: 2 O: 0
 * step = 2000, Average  T: 119 H: 45 C: 0 O: 0
 * step = 5000, Average  T: 121 H: 43 C: 0 O: 0 (有的时候H把T全吃完，有的时候T占主导)
 * 
 * Q5 v 
 * （这里可以画一个拟合图）
 * step = 5，Average  T: 23 H: 23 C: 22 O: 11
 * step = 40，Average  T: 40 H: 21 C: 50 O: 25
 * step = 100, Average  T: 49 H: 6 C: 53 O: 41
 * step = 200, Average  T: 55 H: 1 C: 25 O: 69
 * step = 500, Average  T: 23 H: 0 C: 7 O: 108
 * step = 1000, Average  T: 2 H: 0 C: 5 O: 120
 * step = 2000, Average  T: 0 H: 0 C: 4 O: 122
 * step = 5000, Average  T: 0 H: 0 C: 12 O: 113 (极少情况下只剩C，多数情况下只剩O)
 * 
 * 
 * Question 6 ii）
 * 我无法想到方程式，影响因子太多
 * 但是我可以设计一个暴力程序，测试不同组合下，哪种组合下生物种类不减少维持的最久。
 */

void questionSevenOne(){
    //这一步处，因为我将地形设计为Character中的一类,所以我将simulation->initCharacter(12, '#');替换成读取地形即可。
    //如果要存入更精细的，比如血量信息等，那么就直接存每个Character的坐标，血量信息即可。
    //此处我按照PMA指导书中的格式例子，就不存血量了。
    Simulation* simulation = Simulation::load("../map71.txt");
    simulation->map->display();
}

void questionSevenTwo(){
    Simulation* simulation = Simulation::load("../map71.txt");
    simulation->initCharacter(20, 'T');
    simulation->initCharacter(20, 'H');
    simulation->initCharacter(20, 'C');
    simulation->initCharacter(10, 'O');
    simulation->run(3);
}

void questionSevenThree(){
    Simulation* simulation = new Simulation(14, 14);
    simulation->initCharacter(12, '#');
    simulation->initCharacter(20, 'T');
    simulation->initCharacter(20, 'H');
    simulation->initCharacter(20, 'C');
    simulation->initCharacter(10, 'O');
    
    while (true) {
        char input;
        input = cin.get();
        cin.ignore(256, '\n'); // 忽略缓冲区中的回车键
        if (input == 's') {
            simulation->save("../map73.txt");
            break;
        }
        simulation->run();
    }
}

void questionSevenFour(){
    cout << "Reading the simulation stored in 7 iii) ..." << endl;
    Simulation* simulation = Simulation::load("../map73.txt");
    simulation->map->display();

    cout << "Run one step" << endl;
    simulation->run(1);
}

int main() {
    srand(time(NULL));
    
    // questionTwo();
    // questionThree();
	// questionFour();
    // questionFiveOne();
    // questionFiveTwo();
    // questionFiveThree();
    // questionFiveFour();
    // questionFiveFive();
    // questionFiveSix();
    // questionSevenOne();
    // questionSevenTwo();
    // questionSevenThree();
    questionSevenFour();

    return 0;
}