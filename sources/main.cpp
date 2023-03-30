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
    gameLogic.createCannonBall();

    Ground ground{
        Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60,
        physics.getBody("Ground", Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60, false, BodyType::Box, {0.1f, 0.1f, 0.1f})
    };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE)) {
            gameLogic.playCannonBall();
        }

        physics.makeWorldStep();

        gameLogic.applyPhysicsPositions();
        ground.applyPhysicsPosition();
        gameLogic.applyCannonBallPhysicsPosition();

        gameLogic.checkCannonBallPosiiton();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            gameLogic.drawStage();
            
            gameLogic.drawCannonBall();
            ground.draw();
            debug.draw();
        EndDrawing();

        physics.applyActions();
    }

    CloseWindow();

    return 0;
}