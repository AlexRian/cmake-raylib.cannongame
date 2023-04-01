#pragma once
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include "entities.hpp"
#include "stages.hpp"
#include "./engine/physics.hpp"

enum PlayStates {
	SelectingAngle,
	SelectingForce,
	Moving,
};

class Gamelogic:public b2ContactListener {
private:
	std::vector<PhysicsEntity*> m_stageEntities;
	Physics* m_physics;
	CannonBall* m_cannonBall;
	ForceIndicator m_forceIndicator;
	AngleIndicator m_angleIndicator;
	PlayStates m_currentStage = PlayStates::SelectingAngle;
	bool m_forceScalerMovingUp = true;
	bool m_angleScalerMovingUp = true;
	int m_force = 0;
	int m_angle = 0;

private:
	void scaleForceIndicator() {
		if (m_forceScalerMovingUp) {
			m_force += 10;
			if (m_force == 200) { m_forceScalerMovingUp = false; }
		}
		else {
			m_force -= 10;
			if (m_force == 0) { m_forceScalerMovingUp = true; }
		}
	}
	void scaleAngleIndicator() {
		if (m_angleScalerMovingUp) {
			m_angle += 1;
			if (m_angle == 20) { m_angleScalerMovingUp = false; }
		}
		else {
			m_angle -= 1;
			if (m_angle == 0) { m_angleScalerMovingUp = true; }
		}
	}
public:
	Gamelogic() = default;
	Gamelogic(Physics* physics) 
		:m_physics(physics) 
	{
		m_physics->getWorld()->SetContactListener(this);
		m_forceIndicator = ForceIndicator{ 0, Settings::screenHeight - 100, 90, 30, 10 };
		m_angleIndicator = AngleIndicator{ 200, Settings::screenHeight - 100, 30, 90, 10 };
	};

	void drawIndicators() {
		switch (m_currentStage)
		{
			case SelectingAngle:
				scaleAngleIndicator();
				m_angleIndicator.setSize(Vector2{ 30, (float)m_angle * 10 });
				m_angleIndicator.draw();
				break;
			case SelectingForce:
				scaleForceIndicator();
				m_forceIndicator.setSize(Vector2{ (float)m_force, 30 });
				m_forceIndicator.draw();
				break;
			case Moving:
				break;
			default:
				break;
		}
	}

	void BeginContact(b2Contact* contact) override {
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		std::string bodyAId = *reinterpret_cast<std::string*>(bodyA->GetUserData().pointer);
		std::string bodyBId = *reinterpret_cast<std::string*>(bodyB->GetUserData().pointer);


		//if (bodyAId == "Wall" && bodyBId == "CannonBall") {
		//	m_physics->addPostAction([this]() {
		//		m_cannonBall->switchDynamicState();
		//	});
		//}
	}
	
	void generateStage() {

		for (size_t i = 0; i < stages[0].size(); i++)
		{
			StageEntityData entityData = stages[0][i];

			Wall* wall = new Wall(
				entityData.x, entityData.y, entityData.angle, entityData.width, entityData.height,
				m_physics->getBody("Wall", entityData.x, entityData.y, entityData.angle, entityData.width, entityData.height, true, BodyType::Box, {.2f, 0.3f, 0.5f})
			);

			m_stageEntities.push_back(wall);
		}
	};

	void createCannonBall() {
		m_cannonBall = new CannonBall(
			100, Settings::screenHeight - 200, 90, 30, 30,
			m_physics->getBody("CannonBall", 100, Settings::screenHeight - 200, 90, 30, 30, false, BodyType::Circle, {0.2f, 0.5f, 1.0f})
		);
	}

	void switchPlayState() {
		if (m_currentStage == PlayStates::SelectingForce) {
			m_currentStage = PlayStates::Moving;
			m_cannonBall->switchDynamicState();
			m_cannonBall->applyForce(b2Vec2{ float(5 * m_force), 10 * -(float)m_angle });
		}
		else {
			if (m_currentStage == PlayStates::SelectingAngle) {
				m_currentStage = PlayStates::SelectingForce;
			}
		}
	}

	CannonBall* getCannonBall() {
		return m_cannonBall;
	}

	void applyCannonBallPhysicsPosition() {
		if (m_cannonBall) {
			m_cannonBall->applyPhysicsPosition();
		}
	}

	void checkCannonBallPosiiton() {
		if (m_cannonBall) {
			if (m_cannonBall->getPosition().x < -Settings::screenWidth || m_cannonBall->getPosition().x > Settings::screenWidth * 2) {
				delete m_cannonBall;
				createCannonBall();
				m_currentStage = PlayStates::SelectingAngle;
			}
		}
	}

	void drawCannonBall() {
		if (m_cannonBall) {
			m_cannonBall->draw();
		}
	}

	void drawStage() {
		for (auto entity : m_stageEntities) {
			entity->draw();
		}
	}

	void applyPhysicsPositions() {
		for (auto entity : m_stageEntities) {
			entity->applyPhysicsPosition();
		}
	}
};