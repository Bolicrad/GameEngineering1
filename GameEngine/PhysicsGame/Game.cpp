#include "Game.h"

void Game::OnInit() {
	Engine::Entity<float>* testEntity = new Engine::Entity<float>(sceneRoot, "data\\GoodGuy.dds");
}

void Game::OnUpdate(float dt) {
	
}

void Game::OnBeforeRender() {

}

void Game::OnDestroy() {

}
const char* Game::GetGameName() {
	return "Physics sGame";
};

void Game::OnKey(unsigned int i_VKeyID, bool bWentDown) {
	if (bWentDown == false) {
		switch (i_VKeyID)
		{
		case 27: {
			//Todo: Exit
			break;
		}
		default:
			break;
		}
	}
};