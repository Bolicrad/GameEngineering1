#pragma once
#include "Entity.h"
class Monster :
    public Entity
{
public:
    Monster();
    ~Monster();
    void Wander();
    static Monster* monsters;
    static int monsterCount;
private:
    void Rebirth(const char* reason);
    void SetUp();
};

