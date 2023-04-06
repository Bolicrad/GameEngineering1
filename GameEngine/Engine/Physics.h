#pragma once
#include "Entity.h"
namespace Engine {
	namespace Physics {
		void Update(SmartPtr<Component>& i_Component, float dt);
		void BuildListFromNodeTree(SmartPtr<Entity> root, vector<WeakPtr<Component>>& list);
		void UpdateAll(float dt, vector<WeakPtr<Component>>& list);
	}
}