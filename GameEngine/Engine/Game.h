#pragma once
#include "Entity.h"
class Game
{
public:
	Game(unsigned int width, unsigned int height) :windowWidth(width), windowHeight(height) {
		KeyCallBack = std::bind(&Game::OnKey, this, std::placeholders::_1, std::placeholders::_2);
		sceneRoot = new Engine::Entity<float>();
	};
	~Game() {
		delete sceneRoot;
	}
	void OnInit();
	void OnUpdate(float dt);
	void OnBeforeRender();
	void OnDestroy();
	const char* GetGameName();

	unsigned int windowWidth;
	unsigned int windowHeight;
	std::function<void(unsigned int i_VKeyID, bool bWentDown)> KeyCallBack;
	
	Engine::Entity<float>* sceneRoot;

private:
	void OnKey(unsigned int i_VKeyID, bool bWentDown);
};
