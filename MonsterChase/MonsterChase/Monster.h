#pragma once
#include "Actor.h"
class Monster :
    public Actor
{
public:
    Monster();
    ~Monster();
    void Wander();
    const char* GetName();
    static Monster* monsters;
    static int monsterCount;
private:
    void SetUp();
    void Rebirth(const char* reason);
};

