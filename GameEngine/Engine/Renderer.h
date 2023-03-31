#pragma once
#include "Entity.h"
namespace Engine {
	namespace Renderer {
		void Render(Component* i_Component);
		void BuildListFromNodeTree(SmartPtr<Entity> root, vector<SmartPtr<Component>>& list);
		void RenderAll(vector<SmartPtr<Component>>& list);
	}
}