#pragma once
#include "Engine.h"

class MonsterChase : 
	public Engine::Game 
{
public:
	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnDestroy();
	virtual const char* GetGameName() { return "Monster Chase"; };
	virtual void OnKey(unsigned int i_VKeyID, bool bWentDown);

	MonsterChase(unsigned int width, unsigned int height) {
		windowWidth = width;
		windowHeight = height;
		KeyCallBack = std::bind(&MonsterChase::OnKey, this, std::placeholders::_1, std::placeholders::_2);
	}
};
