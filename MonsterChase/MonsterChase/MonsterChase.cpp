// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Player.h"
#include <iostream>
using namespace std;
int main()
{
    cout << "Welcome to Monster Chase by Lei!" << endl;
    do {
        cout << "Please enter the x Range (input >= 0): ";
        cin >> Entity::xRange;
    } while (Entity::xRange < 0);
    do {
        cout << "Please enter the y Range (input >= 0): ";
        cin >> Entity::yRange;
    } while (Entity::yRange < 0);

    Player player = Player();
}

void Game_Loop() {
    
}