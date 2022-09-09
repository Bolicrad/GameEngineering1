// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Player.h"
#include "Monster.h"
#include "Engine.h"
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
        cout << "Quit..." << endl;
        return false;
        break;
    default:
        cout << "Invalid input. Player ";
        Player::player->PrintName();
        cout << " did nothing." << endl;
        break;
    }

    Player::player->Move(x, y);
    cin.clear();
    cin.ignore(INT_MAX,'\n');

    cout << "Monsters' action time!" << endl;
    for (int i = 0; i < Monster::monsterCount; i++) {
        Monster::monsters[i].Wander();
        if (Monster::monsters[i].x == Player::player->x &&
            Monster::monsters[i].y == Player::player->y) {
            cout << "Player ";
            Player::player->PrintName();
            cout << " is caught by Monster ";
            Monster::monsters[i].PrintName();
            cout << endl;
            return false;
        }
    }

    return true;
}

int main()
{
    EngineInitialization();
    cout << "Welcome to Monster Chase by Lei!" << endl;
    do {
        cout << "Please enter the x Range (input > 0, Range = [-input, input]): ";
        cin >> Entity::xRange;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (Entity::xRange <= 0);
    do {
        cout << "Please enter the y Range (input > 0, Range = [-input, input]): ";
        cin >> Entity::yRange;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (Entity::yRange <= 0);

    do {
        cout << "Please enter the Moster Number (input > 0): ";
        cin >> Monster::monsterCount;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (Monster::monsterCount <= 0);

    cin.ignore();
    Monster::monsters = new Monster[Monster::monsterCount];
    Player::player = new Player();

    cout << "Awesome, let's start the game!" << endl;
    
    while (GameLoop()) {
        cout << "Game Continues..." << endl;
    }

    

    delete Player::player;
    delete[] Monster::monsters;
}

