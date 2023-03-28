#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include "entities.hpp"
#include "stages.hpp"
#include "./engine/physics.hpp"

class Gamelogic {
private:
	std::vector<PhysicsEntity*> m_stageEntities;
	Physics* m_physics;
public:
	Gamelogic() = default;
	Gamelogic(Physics* physics) :m_physics(physics) {};
	
	void generateStage() {

		for (size_t i = 0; i < stages[0].size(); i++)
		{
			StageEntityData entityData = stages[0][i];

			Wall* wall = new Wall(
				entityData.x, entityData.y, entityData.angle, entityData.width, entityData.height,
				m_physics->getBody(entityData.x, entityData.y, entityData.angle, entityData.width, entityData.height, true, BodyType::Box, {.2f, 0.3f, 0.5f})
			);

			m_stageEntities.push_back(wall);
		}
	};

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