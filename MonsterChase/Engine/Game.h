#pragma once
#include "Entity.h"
namespace Engine {
	class Game
	{
	public:
		virtual void OnInit() {};
		virtual void OnUpdate(float dt) {};
		virtual void OnDestroy() {};
		virtual const char* GetGameName() { return nullptr; }
		
		unsigned int windowWidth;
		unsigned int windowHeight;
		std::function<void(unsigned int i_VKeyID, bool bWentDown)> KeyCallBack;
	};
}
