#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "Helper.h"
#include "Point2D.h"
using namespace std;

namespace Engine {
	template <typename T>
	class Entity {
	public:
		Entity<T>(Entity<T>* pParent = nullptr) {
			SetParent(pParent);
		};
		~Entity() {
			if (pSprite != nullptr) GLib::Release(pSprite);
		}
		void PrintPos(Point2D<T> point) {
			cout << "(" << point.getX() << ", " << point.getY() << ")";
		};
		void RenderAtPos() {
			if (pSprite != nullptr) {
				Point2D<T> worldPos = GetWorldPos();
				GLib::Point2D Offset = { worldPos.getX() * 100.0f, worldPos.getY() * 100.0f};
				GLib::Render(*pSprite, Offset, 0.0f, 0.0f);
			}
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
			if (parent)parent->RemoveChild(this);
			Pos = GetWorldPos();
			parent = pParent;
			parent->AddChild(this);
			Pos -= parent->GetWorldPos();
			return true;
		}

		Point2D<T> GetWorldPos() {
			return parent != nullptr ? Pos + parent->GetWorldPos() : Pos;
		}

		Point2D<T> Pos;
		
		GLib::Sprite* pSprite;

		//Node Tree
		Entity<T>* parent = nullptr;
		vector<Entity<T>*> children;
	};
}
