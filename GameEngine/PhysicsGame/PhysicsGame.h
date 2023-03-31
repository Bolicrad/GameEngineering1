#pragma once
#include "Game.h"

class PhysicsGame : public Game {
public: 
	void OnInit() override {
		testEntity = new Engine::Entity(&(*sceneRoot), "data\\GoodGuy.dds", true);
		testEntity->physicsComp->fraction = 3.0f;
	}
	void OnUpdate(float dt) override {};
	void OnBeforeRender() override {};
	void OnDestroy() override {

	};
	const char* GetGameName() override {
		return "PhysicsGame";
	}
protected:
	void OnKey(unsigned int i_VKeyID, bool bWentDown) override {
		if (bWentDown) {
			switch (i_VKeyID) {
			case 65://A
				testEntity->physicsComp->ApplyForce(Point2D<float>::left);
				break;
			case 68://D
				testEntity->physicsComp->ApplyForce(Point2D<float>::right);
				break;
			case 83://S
				testEntity->physicsComp->ApplyForce(Point2D<float>::down);
				break;
			case 87://W
				testEntity->physicsComp->ApplyForce(Point2D<float>::up);
				break;
			default:
				break;
			}
		}
		else {
			switch (i_VKeyID)
			{
			case 27: {
				//Todo: Exit when released
				break;
			}
			case 65://A
				testEntity->physicsComp->ReleaseForce(Point2D<float>::left);
				break;
			case 68://D
				testEntity->physicsComp->ReleaseForce(Point2D<float>::right);
				break;
			case 83://S
				testEntity->physicsComp->ReleaseForce(Point2D<float>::down);
				break;
			case 87://W
				testEntity->physicsComp->ReleaseForce(Point2D<float>::up);
				break;
			default:
				break;
			}
		}
	};
private:
	//Custom Variables
	Engine::SmartPtr<Engine::Entity> testEntity;
};