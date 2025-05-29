#include "raylib.h"
#include "GUI/MenuDirector.hpp"
#include <memory>

int main() {
    // Initialize window
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    SetTargetFPS(60);

    // Create menu director and start with main menu
    MenuDirector director(screenWidth, screenHeight);
    director.transitionTo(MenuType::MAIN);

    // Main game loop
    while (!WindowShouldClose()) {
        director.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        director.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
} 