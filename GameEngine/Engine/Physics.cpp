#include "Physics.h"
namespace Engine {
	namespace Physics {
		void Update(Component* i_Component, float dt) {
			SmartPtr<Entity> obj(i_Component->pEntity);
			if (obj) {
				obj->Pos = i_Component->GetNextPos(dt);
			}
			else {
				i_Component->pEntity = nullptr;
				//Remove the physics component from list
				//Todo
			}
		}
		void BuildListFromNodeTree(SmartPtr<Entity> root) {
			if (root->physicsComp)RigidBodies.push_back(root->physicsComp);
			if (root->children.size() <= 0) return;
			for (auto& child : root->children)BuildListFromNodeTree(child);
		}
		void UpdateAll(float dt)
		{
			for (auto comp : RigidBodies)Update(comp, dt);
		}
	}
}