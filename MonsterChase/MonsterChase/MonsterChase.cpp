// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Player.h"
#include "Monster.h"
#include <iostream>
using namespace std;

bool GameLoop() {
    char input = 'q';
    cout << "Tell me your action (WASD for moving, Q for quit) : " << endl;
    cin >> input;
    int x = 0;
    int y = 0;
    switch (input)
    {
    case 'a':
    case 'A':
        x = -1;
        break;
    case 'd':
    case 'D':
        x = 1;
        break;
    case 's':
    case 'S':
        y = -1;
        break;
    case 'w':
    case 'W':
        y = 1;
        break;
    case 'q':
    case 'Q':
        return false;
        break;
    default:
        cout << "Invalid Input. Player ";
        Player::player->PrintName();
        cout << " not moved." << endl;
        break;
    }
    Player::player->Move(x, y);
    return true;
}

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
    Monster::monsters = new Monster[monsterCount];
    Player::player = new Player();

    cout << "Awesome, let's start the game!" << endl;
    
    while (GameLoop()) {
        cout << "Game Continues..." << endl;
    }

    cout << "Quit..." << endl;

    delete Player::player;
    delete[] Monster::monsters;
}

