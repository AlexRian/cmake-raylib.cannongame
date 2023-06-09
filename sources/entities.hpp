#pragma once
#include "./engine/entity.hpp"
#include "./engine/physics.hpp"
#include "./engine/settings.hpp"

class Wall : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, m_width, m_height};
        DrawRectanglePro(rec, { float(m_width / 2), float(m_height / 2) }, getBodyAngle(), RED);
    }
};

class Ground : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, m_width, m_height };
        DrawRectanglePro(rec, { float(m_width / 2), float(m_height / 2) }, getBodyAngle(), BLACK);
    }
};

class CannonBall : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        DrawCircle(m_position.x, m_position.y, m_width, BLACK);
    }
};

class Enemy : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        DrawCircle(m_position.x, m_position.y, m_width, BLACK);
    }
};

class ForceIndicator : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, m_width, m_height };
        DrawRectanglePro(rec, { 0, float(m_height / 2) }, 0, RED);
    }
};

class AngleIndicator : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, m_width, m_height };
        DrawRectanglePro(rec, { float(m_width / 2), 0 }, 180, BLUE);
    }
};