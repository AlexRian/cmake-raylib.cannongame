#pragma once
#include <Box2D/Box2D.h>
#include "raylib.h"

class Entity
{
protected:
	Vector2 m_position;
	float m_angle;

public:
	Entity() 
		: m_position(Vector2{ 0,0 }), m_angle(180) {};
	Entity(int positionX, int positionY, float angle)
		:m_position{ Vector2{ (float)positionX, (float)positionY } }, m_angle{ angle  } {};
	virtual void draw() {};
	Vector2 getPosition() {
		return m_position;
	};
	void setPosition(Vector2 position) {
		m_position = position;
	};
};