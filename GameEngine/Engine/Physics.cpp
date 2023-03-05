#include "Physics.h"
namespace Engine {
	namespace Physics {
		void Update(Entity<float>* target, float dt) {
			if (target == nullptr)return;
			if (target->physicsComp == nullptr)return;
			target->Pos = target->physicsComp->GetNextPos(dt);
		}

		void UpdateNodeTree(Entity<float>* root, float dt) {
			Update(root, dt);
			if (root->children.size() <= 0) return;
			for (auto child : root->children)UpdateNodeTree(child, dt);
		}
	}
}