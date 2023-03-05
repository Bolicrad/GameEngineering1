#pragma once
#include "Point2D.h"
namespace Engine {
	namespace Physics {
		class Component
		{
		public:
			Component(float i_Mass = 1.0f, float i_Fraction = 0.1f) :
				mass(i_Mass), fraction(i_Fraction) 
			{};

			Point2D<float> GetNextPos(float dt) { //Verlet
				Point2D<float> velocity = currentPos - lastPos;
				Point2D<float> acceleration = (totalForce + CalculateDrag(velocity)) / mass;
				Point2D<float> nextPos = 2.0f * currentPos - lastPos + acceleration * dt;
				lastPos = currentPos;
				currentPos = nextPos;
				return nextPos;
			};

			void ApplyForce(Point2D<float>& i_Force) {
				totalForce += i_Force;
			}
			void ReleaseForce(Point2D<float>& i_Force) {
				totalForce -= i_Force;
			}

			Point2D<float> CalculateDrag(Point2D<float>& velocity) {
				return -velocity * fraction * velocity.Mag2();
			}

			float mass;
			float fraction;
			Point2D<float> lastPos;
			Point2D<float> currentPos;
			Point2D<float> totalForce;
		};
	}
}


