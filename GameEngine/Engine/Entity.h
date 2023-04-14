#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "Point2D.h"
#include "Helper.h"
#include "SmartPtr.h"
#include "WeakPtr.h"
using namespace std;

namespace Engine {
	namespace Physics {
		struct Component;
	}
	namespace Renderer {
		struct Component;
	}

	class Entity {
	public:
		Entity(bool i_isPlayer = false, const char* spritePath = nullptr, bool initPhysics = false)
		{
			isPlayer = i_isPlayer;
			if (spritePath)CreateRenderComp(spritePath);
			if (initPhysics)CreatePhysicComp();
		};
		~Entity() {
			//Delete All children nodes
			children.clear();
			children.shrink_to_fit();
		}

		inline void CreateRenderComp(const char* spritePath);
		inline void CreatePhysicComp();

		void PrintPos(Point2D<float> point) {
			cout << "(" << point.getX() << ", " << point.getY() << ")";
		};

		void AddChild(Entity* pChild) {
			children.push_back(pChild);
		}

		bool RemoveChild(Entity* pChild) {
			for (auto iter = children.begin(); iter != children.end();) {
				if (*iter == SmartPtr<Entity>(pChild)) {
					iter = children.erase(iter);
					return true;
				}
				else iter++;
			}
			return false;
		}
		
		bool HasChild(Entity* pEntity) {
			for (Entity* iter = pEntity; iter != nullptr; iter = iter->parent) {
				if (iter == this) {
					return true;
				}
			}
			return false;
		}

		bool IsChildOf(Entity* pEntity) {
			if (pEntity == nullptr) return false;
			else return pEntity->HasChild(this);
		}

		bool SetParent(Entity* pParent) {
			if (pParent == nullptr || HasChild(pParent)) {
				return false;
			}
			if (parent != nullptr)parent->RemoveChild(this);
			Pos = GetWorldPos();
		
			pParent->AddChild(this);
			Pos -= pParent->GetWorldPos();
			parent = pParent;
			return true;
		}

		Point2D<float> GetWorldPos() {
			return parent != nullptr ? Pos + parent->GetWorldPos() : Pos;
		}

		Point2D<float> Pos;
		bool isPlayer;
		
		//Render Component
		SmartPtr<Renderer::Component> renderComp;

		//Physics Component
		SmartPtr<Physics::Component> physicsComp;

		//Node Tree
		Entity* parent = nullptr;
		vector<SmartPtr<Entity>> children;
	};

	namespace Physics {
		struct Component
		{
		public:
			float mass;
			float fraction;
			WeakPtr<Entity> pEntity;
			Component(SmartPtr<Entity> i_pEntity, float i_Mass = 1.0f, float i_Fraction = 0.3f) :
				pEntity(i_pEntity),
				mass(i_Mass),
				fraction(i_Fraction),
				lastPos(i_pEntity->Pos)
			{}

			Point2D<float> GetNextPos(float dt)
			{ //Midpoint, dt is in ms

				Point2D<float> acceleration = (totalForce + CalculateDrag(lastVel)) / mass;
				Point2D<float> newVel = lastVel + acceleration * dt / 1000.f;

				Point2D<float> nextPos = lastPos + (newVel + lastVel) / 2.0f * dt / 1000.f;

				//#ifdef _DEBUG
				//				const size_t	lenBuffer = 65;
				//				char			Buffer[lenBuffer];
				//
				//				sprintf_s(Buffer, lenBuffer, "vel:(x:%f, y:%f) acc:(x:%f, y:%f)\n", newVel.getX(), newVel.getY(), acceleration.getX(), acceleration.getY());
				//				OutputDebugStringA(Buffer);
				//#endif // __DEBUG

				lastPos = nextPos;
				lastVel = newVel;
				return nextPos;
			}

			void ApplyForce(Point2D<float> i_Force) {
				totalForce += i_Force;
			}
			void ReleaseForce(Point2D<float> i_Force) {
				totalForce -= i_Force;
			}

			Point2D<float> CalculateDrag(Point2D<float>& velocity) {
				return -velocity * fraction * velocity.Mag2();
			}
		private:
			Point2D<float> totalForce;
			Point2D<float> lastVel;
			Point2D<float> lastPos;
		};
	}
	namespace Renderer {
		struct Component {
			WeakPtr<Entity> pEntity;
			GLib::Sprite* pSprite = nullptr;
			Component(SmartPtr<Entity> i_pEntity, const char* spritePath) :
				pEntity(i_pEntity),
				pSprite(Helper::CreateSprite(spritePath))
			{}
			~Component() {
				if (pSprite != nullptr) GLib::Release(pSprite);
			}
		};
	}

	inline void Entity::CreateRenderComp(const char* spritePath)
	{
		renderComp = new Renderer::Component(SmartPtr<Entity>(this), spritePath);
	}

	inline void Entity::CreatePhysicComp()
	{
		physicsComp = new Physics::Component(SmartPtr<Entity>(this));
	}
}
