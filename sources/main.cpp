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
        0, Settings::screenHeight, 180, 8000, 60,
        physics.getBody("Ground", 0, Settings::screenHeight, 180, 8000, 60, false, BodyType::Box, {0.1f, 0.1f, 0.1f})
    };

    Camera2D camera = { 0 };
    camera.target = gameLogic.getCannonBall()->getPosition();
    camera.offset = Vector2{ Settings::screenWidth / 4, Settings::screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE)) {
            gameLogic.switchPlayState();
        }

        if (IsKeyDown(KEY_Z)) {
            camera.zoom = 0.5f;
            camera.offset = Vector2{ Settings::screenWidth / 4, Settings::screenHeight / 2 + 170};
        }
        else {
            camera.offset = Vector2{ Settings::screenWidth / 4, Settings::screenHeight / 2 };
            camera.zoom = 1.0f;
        }

        physics.makeWorldStep();

        gameLogic.applyPhysicsPositions();
        ground.applyPhysicsPosition();
        gameLogic.applyCannonBallPhysicsPosition();

        gameLogic.checkCannonBallPosiiton();

        camera.target = Vector2{ gameLogic.getCannonBall()->getPosition().x + Settings::screenWidth / 8, Settings::screenHeight / 2 };

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                gameLogic.drawStage();
                gameLogic.drawCannonBall();
                gameLogic.drawIndicators();

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