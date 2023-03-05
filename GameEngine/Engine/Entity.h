#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "Helper.h"
#include "Point2D.h"
#include "PhysicsComponent.h"
using namespace std;

namespace Engine {
	template <typename T>
	class Entity {
	public:
		Entity<T>(Entity<T>* pParent = nullptr, const char* spritePath = nullptr, bool initPhysics = false) {
			SetParent(pParent);
			if (spritePath != nullptr)pSprite = Helper::CreateSprite(spritePath);
			if (initPhysics)physicsComp = new Physics::Component();
		};
		~Entity() {
			//Delete Render Component
			if (pSprite != nullptr) GLib::Release(pSprite);

			//Delete Physics Component
			

			//Delete All children nodes
			children.clear();
			children.shrink_to_fit();
		}
		void PrintPos(Point2D<T> point) {
			cout << "(" << point.getX() << ", " << point.getY() << ")";
		};

		void AddChild(Entity<T>* pChild) {
			children.push_back(pChild);
		}

		bool RemoveChild(Entity<T>* pChild) {
			for (auto iter = children.begin(); iter != children.end();) {
				if (*iter == pChild) {
					iter = children.erase(iter);
					return true;
				}
				else iter++;
			}
			return false;
		}
		
		bool HasChild(Entity<T>* pEntity) {
			for (Entity<T>* iter = pEntity; iter != nullptr; iter = iter->parent) {
				if (iter == this) {
					return true;
				}
			}
			return false;
		}

		bool IsChildOf(Entity<T>* pEntity) {
			if (pEntity == nullptr) return false;
			else return pEntity->HasChild(this);
		}

		bool SetParent(Entity<T>* pParent) {
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

		Point2D<T> GetWorldPos() {
			return parent != nullptr ? Pos + parent->GetWorldPos() : Pos;
		}

		Point2D<T> Pos;
		
		//Render Component
		GLib::Sprite* pSprite;

		//Physics Component
		Physics::Component* physicsComp;

		//Node Tree
		Entity<T>* parent = nullptr;
		vector<Entity<T>*> children;
	};
}
