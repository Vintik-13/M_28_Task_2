/*Задание 2. Симуляция работы вокзала

Что нужно сделать
С помощью многопоточности реализуйте простую модель железнодорожного вокзала.
С трёх точек отправления в разное время отбывают три разных поезда с условными
обозначениями A, B, C. Все они идут на один и тот же вокзал и могут дойти до
него в разное время.
На этом целевом вокзале единовременно может находиться только один поезд.
Остальные поезда должны ждать, пока уже занятое место освободится.
В начале программы пользователь последовательно вводит для каждого поезда время
в пути до вокзала (в секундах). После этого поезда начинают своё движение за
заданное количество времени. Как только поезд прибыл на вокзал, он ожидает от
пользователя команды depart, которая сигнализирует о его отбытии с вокзала.
По всем событиям (прибытие на вокзал, ожидание свободного места, отбытие с вокзала)
вместе с условным обозначением поезда выводятся сообщения в консоль.
Программа завершается, когда на вокзале побывают все три поезда.*/

#include "Train.h"

std::mutex coutMutex;
std::mutex trainMutex;
bool isTrainMutex;
COORD pos1;
COORD pos2;

int main()
{
    std::vector<Train*> trains;

    char name{ 65 }; //Для автоматической генерасии имен поездов

    std::string sName{ "" };

    std::string time{ "" };

    for (int i = 0; i < 3; i++) {

        std::cout << "Enter the travel time of the train \"" << name << "\": ";

        std::getline(std::cin, time);

        while (!IsTime(time)) {

            std::cout << "Incorrect input! Try again: ";

            std::getline(std::cin, time);
        }

        std::string sName;
        sName += name;

        Train* tmp = new Train(sName, std::stoi(time));

        name++;

        trains.push_back(tmp);
    }

    pos2 = GetCurPosXY();

    std::vector<std::thread> trainsThread;

    for (auto p : trains) {

        trainsThread.emplace_back(Semaphore, p);
    }

    for (int i = 0; i < 3; i++) {

        trainsThread[i].join();
    }
}