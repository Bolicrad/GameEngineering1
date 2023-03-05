#pragma once
#include "Entity.h"
namespace Engine {
	namespace Renderer {
		static float pixelRate = 100.0f;
		void Render(Entity<float>* target);
		void RenderNodeTree(Entity<float>* root);
	}
}