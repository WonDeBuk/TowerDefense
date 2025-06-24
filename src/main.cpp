#include "raylib.h"
// #include "GUI/MenuDirector.hpp"
// #include <memory>
#include <string>
#include <Game/GameManager.h>
#include "rlgl.h"

int main() {
    const int screenWidth = 1600;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    SetTargetFPS(60);

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