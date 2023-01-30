// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <Windows.h>
#include <iostream>
#include <DirectXColors.h>
#include "Player.h"
#include "Monster.h"
using namespace std;

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG


bool OnPlayerMove(const Point2D& movement) {
    Player::player->Move(movement);
    cout << "Monsters' action time!" << endl;
    for (int i = 0; i < Monster::monsterCount; i++) {
        Monster::monsters[i].Wander();
        if (Monster::monsters[i].Pos == Player::player->Pos) {
            cout << "Player " << Player::player->GetName() << " is caught by Monster "
                << Monster::monsters[i].GetName() << endl;
            return false;
        }
    }
    return true;
}

bool GameLoop() {
    char input = 'q';
    cout << "Tell me your action (WASD for moving, Q for quit) : " << endl;
    cin >> input;
    Point2D movement = Point2D();
    switch (input)
    {
    case 'a':
    case 'A':
        movement.setX(-1);
        break;
    case 'd':
    case 'D':
        movement.setX(1);
        break;
    case 's':
    case 'S':
        movement.setY(-1);
        break;
    case 'w':
    case 'W':
        movement.setY(1);
        break;
    case 'q':
    case 'Q':
        cout << "Quit..." << endl;
        return false;
        break;
    default:
        cout << "Invalid input. Player " << Player::player->GetName() << " did nothing." << endl;
        break;
    }

    cin.clear();
    cin.ignore(INT_MAX, '\n');

    return OnPlayerMove(movement);
}

void KeyCallBack(unsigned int i_VKeyID, bool bWentDown) {
#ifdef _DEBUG
    const size_t	lenBuffer = 65;
    char			Buffer[lenBuffer];

    sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
    OutputDebugStringA(Buffer);
#endif // __DEBUG

    //Get WSAD inputs to move the character
    if (bWentDown == false) {
        Point2D movement = Point2D();
        switch (i_VKeyID) {
        case 65://A
            movement.setX(-1);
            break;
        case 68://D
            movement.setX(1);
            break;
        case 83://S
            movement.setY(-1);
            break;
        case 87://W
            movement.setY(1);
            break;
        default: return;
        }
        OnPlayerMove(movement);
    }
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
    EngineInitialization();
    cout << "Welcome to Monster Chase by Lei!" << endl;

    int xRange = 4;
    //int xRange;
    //do {
    //    cout << "Please enter the x Range (input > 0, Range = [-input, input]): ";
    //    cin >> xRange;
    //    if (cin.fail()) {
    //        cin.clear();
    //        cin.ignore(INT_MAX, '\n');
    //    }
    //} while (xRange <= 0);
    
    int yRange = 4;
    //int yRange;
    //do {
    //    cout << "Please enter the y Range (input > 0, Range = [-input, input]): ";
    //    cin >> yRange;
    //    if (cin.fail()) {
    //        cin.clear();
    //        cin.ignore(INT_MAX, '\n');
    //    }
    //} while (yRange <= 0);
    
    Entity::range = Point2D(xRange, yRange);

    Monster::monsterCount = 3;
    //do {
    //    cout << "Please enter the Moster Number (input > 0): ";
    //    cin >> Monster::monsterCount;
    //    if (cin.fail()) {
    //        cin.clear();
    //        cin.ignore(INT_MAX, '\n');
    //    }
    //} while (Monster::monsterCount <= 0);
    //cin.ignore();

    //Previous Game Loop
    //while (GameLoop()) {
    //    cout << "Game Continues..." << endl;
    //}

    bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Chase", -1, 900, 900, true);

    if (bSuccess) {
        GLib::SetKeyStateChangeCallback(KeyCallBack);

        //Construct monsters and player, the Sprite is created inside the class
        Monster::monsters = new Monster[Monster::monsterCount];
        Player::player = new Player();

        bool bQuit = false;

        do {
            GLib::Service(bQuit);

            if (!bQuit) {
                GLib::BeginRendering(DirectX::Colors::Blue);
                GLib::Sprites::BeginRendering();

                //Render All the Entities
                Player::player->RenderAtPos();
                for (int i = 0; i < Monster::monsterCount; i++) {
                    Monster::monsters[i].RenderAtPos();
                }

                GLib::Sprites::EndRendering();
                GLib::EndRendering();
            }

        } while (bQuit == false);

        delete Player::player;
        delete[] Monster::monsters;
        
        GLib::Shutdown();
    }
    
#if defined _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG

}

