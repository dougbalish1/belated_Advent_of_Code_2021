#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include "fishClassST.hpp"

#define individualMode true

atomic<int> atomic_count{0};
stack<Fish> fishQ;

void runFish();

int main(int argc, char **argv){
    ifstream inFile("../input_6.txt");
    string inLine;

    int daysToRun = (argc > 1) ? atoi(argv[1]) : 80;
    
    getline(inFile, inLine);
    inFile.close();
    for(int i = 0; i < inLine.length(); i+=2)
        fishQ.push(Fish(0, daysToRun, inLine[i] - '0'));

    runFish();

    cout << atomic_count << '\n';

    return 0;
}


#if individualMode
void runFish(){
    while(!fishQ.empty()){
        Fish curFish = fishQ.top();
        fishQ.pop();
        curFish.live(fishQ);
        atomic_count++;
    }
}

#else
void runFish(){
    stack<Fish> offspring;
    while (true){
        if(fishQ.empty())
            return;
        Fish curFish = fishQ.top();
        fishQ.pop();
        offspring = curFish.live();
        while(!offspring.empty()){
            fishQ.push(offspring.top());
            offspring.pop();
        }
        ++atomic_count;
    }
}
#endif