#pragma once
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include "entities.hpp"
#include "stages.hpp"
#include "./engine/physics.hpp"

class Gamelogic:public b2ContactListener {
private:
	std::vector<PhysicsEntity*> m_stageEntities;
	Physics* m_physics;
	CannonBall* m_cannonBall;
public:
	Gamelogic() = default;
	Gamelogic(Physics* physics) 
		:m_physics(physics) 
	{
		m_physics->getWorld()->SetContactListener(this);
	};

	void BeginContact(b2Contact* contact) override {
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		std::string bodyAId = *reinterpret_cast<std::string*>(bodyA->GetUserData().pointer);
		std::string bodyBId = *reinterpret_cast<std::string*>(bodyB->GetUserData().pointer);


		if (bodyAId == "Wall" && bodyBId == "CannonBall") {
			m_physics->addPostAction([this]() {
				m_cannonBall->switchDynamicState();
			});
		}
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

	void playCannonBall() {
		if (m_cannonBall && m_cannonBall->getBodyVelocty().x == 0) {
			m_cannonBall->switchDynamicState();
			m_cannonBall->applyForce(b2Vec2{ 300, -60 });
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
			if (m_cannonBall->getPosition().x < 0 || m_cannonBall->getPosition().x > Settings::screenWidth) {
				delete m_cannonBall;
				createCannonBall();
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