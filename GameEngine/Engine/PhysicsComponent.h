#pragma once
#include "Point2D.h"
namespace Engine {
	namespace Physics {
		class Component
		{
		public:
			Component(float i_Mass = 1.0f, float i_Fraction = 0.3f) :
				mass(i_Mass), fraction(i_Fraction) 
			{};

			Point2D<float> GetNextPos(float dt) { //Midpoint, dt is in ms
				Point2D<float> acceleration = (totalForce + CalculateDrag(lastVel)) / mass;
				Point2D<float> newVel = lastVel + acceleration * dt / 1000.f;
				
				Point2D<float> nextPos = lastPos + (newVel + lastVel) / 2.0f * dt / 1000.f;

#ifdef _DEBUG
				const size_t	lenBuffer = 65;
				char			Buffer[lenBuffer];

				sprintf_s(Buffer, lenBuffer, "vel:(x:%f, y:%f) acc:(x:%f, y:%f)\n", newVel.getX(), newVel.getY(), acceleration.getX(), acceleration.getY());
				OutputDebugStringA(Buffer);
#endif // __DEBUG
				lastPos = nextPos;
				lastVel = newVel;
				return nextPos;
			};

			void ApplyForce(Point2D<float> i_Force) {
				totalForce += i_Force;
			}
			void ReleaseForce(Point2D<float> i_Force) {
				totalForce -= i_Force;
			}

			Point2D<float> CalculateDrag(Point2D<float>& velocity) {
				return -velocity * fraction * velocity.Mag2();
			}

			float mass;
			float fraction;
			Point2D<float> lastVel;
			Point2D<float> lastPos;
			Point2D<float> totalForce;
		};
	}
}


