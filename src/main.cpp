#include "raylib.h"
#include "GUI/MenuDirector.hpp"
#include <memory>
#include <string>
#include <Game/GameManager.h>

std::string texturePath = std::string(ASSETS_PATH) + "/textures/ui/Slime.png";
Texture2D* ZombieTexture = nullptr;

int main() {
    // Initialize window
    const int screenWidth = 1600;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    SetTargetFPS(60);
    ZombieTexture = &LoadTexture(texturePath.c_str());
    GameManager::GetInstance().AddEnemy(ZOMBIE);

    // Main game loop
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        GameManager::GetInstance().Draw();

        EndDrawing();
        GameManager::GetInstance().Update();
    }

    CloseWindow();
    return 0;
}