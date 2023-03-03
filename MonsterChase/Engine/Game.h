#pragma once
namespace Engine {
	class Game
	{
	public:
		virtual void OnInit() {};
		virtual void OnUpdate() {};
		virtual void OnDestroy() {};
		virtual const char* GetGameName() { return nullptr; }
		virtual void OnKey(unsigned int i_VKeyID, bool bWentDown) {};
		
		unsigned int windowWidth;
		unsigned int windowHeight;
		std::function<void(unsigned int i_VKeyID, bool bWentDown)> KeyCallBack;
	};
}
