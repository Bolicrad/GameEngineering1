#pragma once
#include "Actor.h"
class Player :
    public Actor
{
public:
    Player();
    ~Player();
    const char* GetName();
    static Player* player;
private:
    void SetUp();
};