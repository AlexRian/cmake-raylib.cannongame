#include <stdio.h>
#include "raylib.h"
#include "./engine/debug.hpp"
#include "./engine/physics.hpp"
#include "./entities.hpp"
#include "./gamelogic.hpp"

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Cannon Game");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    Physics physics{ b2Vec2{0.f, 9.8f} };

    Gamelogic gameLogic(&physics);
    gameLogic.generateStage();

    Ground ground{
        Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60,
        physics.getBody(Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60, false, BodyType::Box, {0.1f, 0.1f, 0.1f})
    };

    CannonBall cannonBall{
        100, Settings::screenHeight - 200, 90, 30, 30,
        physics.getBody(100, Settings::screenHeight - 200, 90, 30, 30, false, BodyType::Circle, {0.2f, 0.5f, 1.0f})
    };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE)) {
            cannonBall.switchDynamicState();
            cannonBall.applyForce(b2Vec2{300, -60});
        }

        physics.makeWorldStep();

        gameLogic.applyPhysicsPositions();
        ground.applyPhysicsPosition();
        cannonBall.applyPhysicsPosition();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            gameLogic.drawStage();
            
            cannonBall.draw();
            ground.draw();
            debug.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}