#pragma once
#include "Entity.h"
class Monster :
    public Entity
{
public:
    Monster();
    ~Monster();

    static Monster* monsters;
};

