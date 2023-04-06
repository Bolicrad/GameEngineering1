#include "Physics.h"
namespace Engine {
	namespace Physics {
		void Update(SmartPtr<Component>& i_Component, float dt) {
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
		void BuildListFromNodeTree(SmartPtr<Entity> root, vector<WeakPtr<Component>>& list) {
			if (root->physicsComp)list.push_back(root->physicsComp);
			if (root->children.size() <= 0) return;
			for (auto& child : root->children)BuildListFromNodeTree(child, list);
		}
		void UpdateAll(float dt, vector<WeakPtr<Component>>& list)
		{
			
			for (auto& wpComp : list) {
				SmartPtr<Component> spComp(wpComp);
				if (spComp) {
					Update(spComp, dt);
				}
				else {
					//Remove the weakPtr from list
					//Todo
				}
			}
		}
	}
}