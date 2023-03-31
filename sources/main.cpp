#include <stdio.h>
#include "raylib.h"
#include "./engine/debug.hpp"
#include "./engine/physics.hpp"
#include "./entities.hpp"
#include "./gamelogic.hpp"
#include "./engine/assetsManager.hpp"

std::vector<TextureData> textureData{
    {"enemy", ASSETS_PATH"enemy.png"}
};

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Cannon Game");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    Physics physics{ b2Vec2{0.f, 9.8f} };
    AssetsManager assetsManager{ textureData };

    Gamelogic gameLogic(&physics);
    gameLogic.generateStage();
    gameLogic.createCannonBall();

    Ground ground{
        Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60,
        physics.getBody("Ground", Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60, false, BodyType::Box, {0.1f, 0.1f, 0.1f})
    };

    Camera2D camera = { 0 };
    camera.target = gameLogic.getCannonBall()->getPosition();
    camera.offset = Vector2{ Settings::screenWidth / 2, Settings::screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

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

        camera.target = gameLogic.getCannonBall()->getPosition();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                gameLogic.drawStage();

                gameLogic.drawCannonBall();
                ground.draw();
                debug.draw();
            EndMode2D();
        EndDrawing();

        physics.applyActions();
    }

    assetsManager.unloadTextures();
    CloseWindow();

    return 0;
}