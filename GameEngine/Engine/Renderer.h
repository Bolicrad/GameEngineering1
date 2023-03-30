#pragma once
#include "Entity.h"
namespace Engine {
	namespace Renderer {
		static float pixelRate = 100.0f;
		static vector<Component*> RenderList = vector<Component*>();
		void Render(Component* i_Component);
		void BuildListFromNodeTree(SmartPtr<Entity> root);
		void RenderAll();
	}
}