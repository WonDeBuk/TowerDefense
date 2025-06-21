#include "raylib.h"
#include "GUI/MenuDirector.hpp"
#include <memory>
#include <string>
#include <Game/GameManager.h>

std::string texturePath = std::string(ASSETS_PATH) + "/textures/ui/Slime.png";
std::string healthBarPath = std::string(ASSETS_PATH) + "/textures/ui/HealthBar.png";
Texture2D* ZombieTexture = nullptr;
Texture2D* HealthBar = nullptr;

int main() {
    // Initialize window
    const int screenWidth = 1600;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    SetTargetFPS(60);
    ZombieTexture = &LoadTexture(texturePath.c_str());
    HealthBar = &LoadTexture(healthBarPath.c_str());
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