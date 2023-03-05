#include "Renderer.h"
#include "Helper.h"
namespace Engine {
	namespace Renderer {
		void Render(Entity<float>* target)
		{
			if (target->pSprite == nullptr) return;
			Point2D<float> worldPos = target->GetWorldPos();
			GLib::Point2D Offset = { worldPos.getX() * pixelRate, worldPos.getY() * pixelRate };
			GLib::Render(*target->pSprite, Offset, 0.0f, 0.0f);

		}
		void RenderNodeTree(Entity<float>* root)
		{
			Render(root);
			if (root->children.size() <= 0) return;
			for (auto child : root->children)RenderNodeTree(child);
		}
	}
}