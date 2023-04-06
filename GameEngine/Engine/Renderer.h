#pragma once
#include "Entity.h"
namespace Engine {
	namespace Renderer {
		void Render(SmartPtr<Component> i_Component);
		void BuildListFromNodeTree(SmartPtr<Entity> root, vector<WeakPtr<Component>>& list);
		void RenderAll(vector<WeakPtr<Component>>& list);
	}
}