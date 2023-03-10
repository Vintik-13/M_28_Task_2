#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <regex>

extern std::mutex coutMutex;
extern std::mutex trainMutex;
extern bool isTrainMutex;
extern COORD pos1;
extern COORD pos2;

class Train {

    std::string name;

    int time;

public:

    Train(std::string name, int time) :name(name), time(time) {}

    void SetTime(int time);

    std::string GetName(); 

    int GetTime();
};

void SetCurPosXY(const short x, const short int y); 

COORD GetCurPosXY(); 

void TrainStationLock(Train* t); 

void Semaphore(Train* t);

bool IsTime(const std::string speed); //Валидация ввода положительного числа


