#include "Game.h"
#include "Player.h"
#include "Monster.h"

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

void Game::OnInit()
{
    int xRange = 4;
    int yRange = 4;
    Actor::range = Point2D<int>(xRange, yRange);
    Monster::monsterCount = 3;

    Monster::monsters = new Monster[Monster::monsterCount];
    Player::player = new Player();
}

void Game::OnUpdate(float dt)
{
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

}

void Game::OnBeforeRender() {
    Player::player->RenderAtPos();
    for (int i = 0; i < Monster::monsterCount; i++) {
        Monster::monsters[i].RenderAtPos();
    }
}

void Game::OnDestroy()
{
    delete Player::player;
    delete[] Monster::monsters;
}

const char* Game::GetGameName()
{
    return "Monster Chase";
}

void Game::OnKey(unsigned int i_VKeyID, bool bWentDown) {
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