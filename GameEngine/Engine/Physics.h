#pragma once
#include "Entity.h"
namespace Engine {
	namespace Physics {
		void Update(Component* i_Component, float dt);
		void BuildListFromNodeTree(SmartPtr<Entity> root, vector<SmartPtr<Component>>& list);
		void UpdateAll(float dt, vector<SmartPtr<Component>>& list);
	}
}