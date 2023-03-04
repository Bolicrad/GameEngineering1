#pragma once
#include <iostream>
#include "Helper.h"
#include "Point2D.h"
using namespace std;

namespace Engine {
	template <typename T>
	class Entity {
	public:
		~Entity() {
			if (pSprite != nullptr) GLib::Release(pSprite);
		}
		void PrintPos(Point2D<T> point) {
			cout << "(" << point.getX() << ", " << point.getY() << ")";
		};
		void RenderAtPos() {
			if (pSprite != nullptr) {
				GLib::Point2D Offset = { Pos.getX() * 100.0f, Pos.getY() * 100.0f };
				GLib::Render(*pSprite, Offset, 0.0f, 0.0f);
			}
		};

		Point2D<T> Pos;

	protected:
		GLib::Sprite* pSprite;
	};
}
