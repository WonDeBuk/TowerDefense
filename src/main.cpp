#include "raylib.h"
// #include "GUI/MenuDirector.hpp"
// #include <memory>
#include <string>
#include <Game/GameManager.h>
#include "rlgl.h"

std::string texturePath = std::string(ASSETS_PATH) + "/textures/ui/Slime.png";
std::string healthBarPath = std::string(ASSETS_PATH) + "/textures/ui/HealthBar.png";
std::string mapPath = std::string(ASSETS_PATH) + "/textures/ui/Map.png";
std::string FrierenPath = std::string(ASSETS_PATH) + "/textures/ui/Frieren.png";
std::string FernPath = std::string(ASSETS_PATH) + "/textures/ui/Fern.png";
std::string LeavesPath = std::string(ASSETS_PATH) + "/textures/ui/Leaves.png";
std::string LaserPath = std::string(ASSETS_PATH) + "/textures/ui/Laser.png";
std::string AuraPath = std::string(ASSETS_PATH) + "/textures/ui/Aura.png";
Texture2D* ZombieTexture = nullptr;
Texture2D* HealthBar = nullptr;
Texture2D* Map = nullptr;
Texture2D* Frieren = nullptr;
Texture2D* Fern = nullptr;
Texture2D* Leaves = nullptr;
Texture2D* Laser = nullptr;
Texture2D* Aura = nullptr;

int main() {
    // Initialize window
    const int screenWidth = 1600;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    SetTargetFPS(60);
    ZombieTexture = &LoadTexture(texturePath.c_str());
    HealthBar = &LoadTexture(healthBarPath.c_str());
    Map = &LoadTexture(mapPath.c_str());
    Frieren = &LoadTexture(FrierenPath.c_str());
    Fern = &LoadTexture(FernPath.c_str());
    Leaves = &LoadTexture(LeavesPath.c_str());
    Laser = &LoadTexture(LaserPath.c_str());
    Aura = &LoadTexture(AuraPath.c_str());
    Vector2 Centre = {(float) screenWidth / 2, (float) screenHeight / 2};
    float Time = 0;

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        GameManager::GetInstance().Draw();

        GameManager::GetInstance().Update();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}