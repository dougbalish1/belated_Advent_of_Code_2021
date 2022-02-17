#include <stack>
using namespace std;

class Fish{
    int day, stopDay, timer;

    public:
    Fish(int, int, int);
    Fish(int, int);
    void live(stack<Fish>&);
};

Fish::Fish(int daySpawned, int stop, int daysToReproduce){
    day = daySpawned;
    stopDay = stop;
    timer = daysToReproduce;
}

Fish::Fish(int daySpawned, int stop){
    day = daySpawned;
    stopDay = stop;
    timer = 8;
}

void Fish::live(stack<Fish>& fishQ){
    while(day < stopDay){
            if(timer == 0){
                fishQ.push(Fish(day + 1, stopDay));
                day += 7;
            }
            else{
                timer--;
                day++;
            }
    }
}