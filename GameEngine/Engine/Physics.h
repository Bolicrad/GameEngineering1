#pragma once
#include "Entity.h"
namespace Engine {
	namespace Physics {
		void Update(Entity<float>* target, float dt);
		void UpdateNodeTree(Entity<float>* root, float dt);
	}
}