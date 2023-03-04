#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "MonsterChase.h"
using namespace std;

bool OnPlayerMove(const Point2D<int>& movement) {
    cout << "Player Moving" << endl;
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

//bool GameLoop() {
//    char input = 'q';
//    cout << "Tell me your action (WASD for moving, Q for quit) : " << endl;
//    cin >> input;
//    Point2D movement = Point2D();
//    switch (input)
//    {
//    case 'a':
//    case 'A':
//        movement.setX(-1);
//        break;
//    case 'd':
//    case 'D':
//        movement.setX(1);
//        break;
//    case 's':
//    case 'S':
//        movement.setY(-1);
//        break;
//    case 'w':
//    case 'W':
//        movement.setY(1);
//        break;
//    case 'q':
//    case 'Q':
//        cout << "Quit..." << endl;
//        return false;
//        break;
//    default:
//        cout << "Invalid input. Player " << Player::player->GetName() << " did nothing." << endl;
//        break;
//    }
//
//    cin.clear();
//    cin.ignore(INT_MAX, '\n');
//
//    return OnPlayerMove(movement);
//}

void MonsterChase::OnKey(unsigned int i_VKeyID, bool bWentDown) {
#ifdef _DEBUG
    const size_t	lenBuffer = 65;
    char			Buffer[lenBuffer];

    sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
    OutputDebugStringA(Buffer);
#endif // __DEBUG
    cout << "Dealing Input:" << endl;
    //Get WSAD inputs to move the character
    if (bWentDown == false) {
        Point2D<int> movement = Point2D<int>();
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

void MonsterChase::OnInit() {
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

    Actor::range = Point2D<int>(xRange, yRange);

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

    //Construct monsters and player, the Sprite is created inside the class
    Monster::monsters = new Monster[Monster::monsterCount];
    Player::player = new Player();
}

void MonsterChase::OnUpdate(float dt) {
    //Render All the Entities
#ifdef _DEBUG
    static float timer = 0;
    static unsigned int framerate = 0;
    timer += dt;
    if (timer > 1000.0f) {
        const size_t	lenBuffer = 65;
        char			Buffer[lenBuffer];
        sprintf_s(Buffer, lenBuffer, "Current Frame time(ms): %f\n", dt);
        OutputDebugStringA(Buffer);
        timer -= 1000.0f;
    }
#endif // _DEBUG

    Player::player->RenderAtPos();
    for (int i = 0; i < Monster::monsterCount; i++) {
        Monster::monsters[i].RenderAtPos();
    }
}

void MonsterChase::OnDestroy() {
    delete Player::player;
    delete[] Monster::monsters;
}