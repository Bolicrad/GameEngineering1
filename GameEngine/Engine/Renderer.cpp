#include "Renderer.h"
namespace Engine {
	namespace Renderer {
		void Render(SmartPtr<Component> i_Component)
		{
			float pixelRate = 100.0f;
			SmartPtr<Entity> obj(i_Component->pEntity);
			if (obj) {
				Point2D<float> worldPos = obj->GetWorldPos();
				GLib::Point2D Offset = { worldPos.getX() * pixelRate, worldPos.getY() * pixelRate };
				GLib::Render(*i_Component->pSprite, Offset, 0.0f, 0.0f);
			}
			else {
				//Release weak ptr of the render component
				i_Component->pEntity = nullptr;
				//Remove the render component from global list
				//Todo
			}
		}
		void BuildListFromNodeTree(SmartPtr<Entity> root, vector<WeakPtr<Component>>& list)
		{
			if (root->renderComp)list.push_back(root->renderComp);
			if (root->children.size() <= 0) return;
			for (auto& child : root->children) BuildListFromNodeTree(child,list);
		}
		void RenderAll(vector<WeakPtr<Component>>& list)
		{
			for (auto& wpComp : list) { 
				SmartPtr<Component> spComp(wpComp);
				if (spComp) {
					Render(spComp);
				}
				else {
					//Remove the component
					//Todo (might need to use different iteration)
				}
			}
		}
	}
}