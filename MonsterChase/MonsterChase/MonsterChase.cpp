// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Player.h"
#include "Monster.h"
#include <iostream>
using namespace std;
int main()
{
    cout << "Welcome to Monster Chase by Lei!" << endl;
    do {
        cout << "Please enter the x Range (input > 0, Range = [-input, input]): ";
        cin >> Entity::xRange;
    } while (Entity::xRange <= 0);
    do {
        cout << "Please enter the y Range (input > 0, Range = [-input, input]): ";
        cin >> Entity::yRange;
    } while (Entity::yRange <= 0);

    int monsterCount = 0;
    do {
        cout << "Please enter the Moster Number (input > 0): ";
        cin >> monsterCount;
    } while (monsterCount <= 0);

    cin.ignore();
    Monster* monsters = new Monster[monsterCount];
    Player player = Player();
    

    
}

void Game_Loop() {
    
}