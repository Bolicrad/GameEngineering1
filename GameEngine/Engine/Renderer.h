#pragma once
#include "Entity.h"
namespace Engine {
	namespace Renderer {
		float pixelRate = 100.0f;
		void Render(Entity<float>* target);
		bool RenderNodeTree(Entity<float>* root);
	}
}