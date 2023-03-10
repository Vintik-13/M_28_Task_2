#include "Train.h"

void Train::SetTime(int time) { this->time = time; }

std::string Train::GetName() { return name; }

int Train::GetTime() { return time; }

void SetCurPosXY(const short x, const short int y) {

	COORD p = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

COORD GetCurPosXY() {
	
    CONSOLE_SCREEN_BUFFER_INFO buf;

    COORD tmp = { 0, 0 };

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buf)) {

        tmp.X = buf.dwCursorPosition.X;
        tmp.Y = buf.dwCursorPosition.Y;

        return tmp;
    }
    return tmp;
}

void TrainStationLock(Train* t) {

    std::string depart{ "" };

    trainMutex.lock();
    isTrainMutex = true;

    coutMutex.lock();
    std::cout << "Train " << "\"" << t->GetName() << "\"" << " arrival at the train station! Depart? ";

    pos1 = GetCurPosXY();

    pos2.Y++;
    coutMutex.unlock();

    std::getline(std::cin, depart);

    while (depart != "Depart") {

        coutMutex.lock();
        pos2 = GetCurPosXY();

        SetCurPosXY(0, pos2.Y);

        std::cout << "Enter the command \"Depart\"";

        SetCurPosXY(pos1.X, pos2.Y);
        coutMutex.unlock();

        std::getline(std::cin, depart);
    }

    isTrainMutex = false;
    trainMutex.unlock();
}

void Semaphore(Train* t) {

    while (t->GetTime() > 0) {

        std::this_thread::sleep_for(std::chrono::seconds(1));

        t->SetTime(t->GetTime() - 1);
    }

    if (isTrainMutex == false) {

        coutMutex.lock();
        SetCurPosXY(0, pos2.Y + 1);
        coutMutex.unlock();

        TrainStationLock(t);
    }
    else {

        coutMutex.lock();
        SetCurPosXY(0, pos2.Y + 1);

        std::cout << "Train " << "\"" << t->GetName() << "\"" << " waiting for free space!";

        pos2 = GetCurPosXY();

        SetCurPosXY(pos1.X, pos1.Y);
        coutMutex.unlock();

        while (isTrainMutex == true) {}

        coutMutex.lock();
        SetCurPosXY(0, pos2.Y + 1);
        coutMutex.unlock();

        TrainStationLock(t);
    }
}

bool IsTime(const std::string speed) {
    
    std::regex pattern("\\d*");

    return std::regex_match(speed.c_str(), pattern) ? true : false;
}
