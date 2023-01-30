#pragma once
#include "Entity.h"
class Player :
    public Entity
{
public:
    Player();
    ~Player();
    const char* GetName();
    static Player* player;
private:
    void SetUp();
};

