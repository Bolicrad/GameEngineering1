#pragma once
#include "Game.h"

class MyGame : public Game {
public:
	void OnInit() override {}
	void OnUpdate(float dt) override {};
	void OnBeforeRender() override {};
	void OnDestroy() override {};
	const char* GetGameName() override {
		return "MyGame";
	}
protected:
	void OnKey(unsigned int i_VKeyID, bool bWentDown) override {

	};
private:
	//Custom Variables

};