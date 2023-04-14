#pragma once
#include "Game.h"

class PhysicsGame : public Game {
public: 
	void OnInit() override {};
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
				player->physicsComp->ApplyForce(Point2D<float>::left);
				break;
			case 68://D
				player->physicsComp->ApplyForce(Point2D<float>::right);
				break;
			case 83://S
				player->physicsComp->ApplyForce(Point2D<float>::down);
				break;
			case 87://W
				player->physicsComp->ApplyForce(Point2D<float>::up);
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
				player->physicsComp->ReleaseForce(Point2D<float>::left);
				break;
			case 68://D
				player->physicsComp->ReleaseForce(Point2D<float>::right);
				break;
			case 83://S
				player->physicsComp->ReleaseForce(Point2D<float>::down);
				break;
			case 87://W
				player->physicsComp->ReleaseForce(Point2D<float>::up);
				break;
			default:
				break;
			}
		}
	};
};