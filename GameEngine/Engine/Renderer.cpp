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
		bool RenderNodeTree(Entity<float>* root)
		{
			Render(root);
			if (root->children.size() <= 0) return false;
			else {
				for (auto node : root->children)RenderNodeTree(node);
			}
		}
	}
}