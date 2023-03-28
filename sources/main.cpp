#include <stdio.h>
#include "raylib.h"
#include "./engine/debug.hpp"
#include "./engine/physics.hpp"
#include "./entities.hpp"
#include "./gamelogic.hpp"

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Game");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    Physics physics{ b2Vec2{0.f, 9.8f} };

    Gamelogic gameLogic(&physics);
    gameLogic.generateStage();

    Ground ground{
        Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60,
        physics.getBody<b2PolygonShape>(Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60, false, {0.1f, 0.1f, 0.1f})
    };

    CannonBall cannonBall{
        100, Settings::screenHeight - 200, 90, 30, 30,
        physics.getBody<b2CircleShape>(100, Settings::screenHeight - 200, 90, 30, 30, false, {0.1f, 0.1f, 0.1f})
    };

    while (!WindowShouldClose())
    {

        physics.makeWorldStep();

        gameLogic.applyPhysicsPositions();
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