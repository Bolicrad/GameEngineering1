#pragma once
#include "Entity.h"
class Monster :
    public Entity
{
public:
    Monster();
    ~Monster();
    void Wander();
    const char* GetName();
    static Monster* monsters;
    static int monsterCount;
private:
    void Rebirth(const char* reason);
    void SetUp();
};

