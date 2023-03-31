#pragma once
#include "Entity.h"

class Game
{
public:
	Game(int width = 900, int height = 900) :windowWidth(width), windowHeight(height) {
		
		KeyCallBack = std::bind(&Game::OnKey, this, std::placeholders::_1, std::placeholders::_2);
		sceneRoot = new Engine::Entity();
	};
	virtual void OnInit() {};
	virtual void OnUpdate(float dt) {};
	virtual void OnBeforeRender() {};
	virtual void OnDestroy() {};
	virtual const char* GetGameName() { return "Game"; };

	int windowWidth;
	int windowHeight;
	std::function<void(unsigned int i_VKeyID, bool bWentDown)> KeyCallBack;
	
	Engine::SmartPtr<Engine::Entity> sceneRoot = nullptr;

protected:
	virtual void OnKey(unsigned int i_VKeyID, bool bWentDown) {};
};
