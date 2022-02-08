#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include "fishClass.hpp"

atomic<int> atomic_count{0};
vector<stack<Fish>*> stackVec;

void runFish(int i);

int main(int argc, char **argv){
    vector<thread> threads;
    string inLine;
    int numThreads = (thread::hardware_concurrency() > 2) ? thread::hardware_concurrency() - 2 : 2;
    numThreads = (argc > 2) ? atoi(argv[2]) : numThreads;
    int daysToRun = (argc > 1) ? atoi(argv[1]) : 80;
    ifstream inFile("../input_6.txt");
    vector<int> balanceFish;

    getline(inFile, inLine);
    inFile.close();

    for(int i = 0; i < inLine.length(); i+=2)
        balanceFish.push_back(inLine[i] - '0');

    sort(balanceFish.begin(), balanceFish.end());
    for(int i = 0; i < numThreads; i++){
        stackVec.push_back(new stack<Fish>);
        int j = i;
        while(j < balanceFish.size()){
            stackVec[i]->push(Fish(0, daysToRun, balanceFish[j]));
            j += numThreads;
        }
    }

    for(int i = 0; i < numThreads; i++)
        threads.push_back(std::thread(runFish, i));
    
    for(int i = 0; i < numThreads; i++)
        threads[i].join();

    cout << atomic_count << '\n';

    return 0;
}

void runFish(int i){
    while(!stackVec[i]->empty()){
        Fish curFish = stackVec[i]->top();
        stackVec[i]->pop();
        curFish.live(*stackVec[i]);
        atomic_count++;
    }
}