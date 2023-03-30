#pragma once
#include "Entity.h"
namespace Engine {
	namespace Physics {
		static vector<Component*> RigidBodies = vector<Component*>();
		void Update(Component* i_Component, float dt);
		void BuildListFromNodeTree(SmartPtr<Entity> root);
		void UpdateAll(float dt);
	}
}