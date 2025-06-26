#include "raylib.h"
#include "rlgl.h"

#include "GUI/Director.h"
#include "Utils/AssetManager.h"
#include "Game/GameManager.h"

#include <string>
#include <iostream>
#include <thread>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 960

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower Defense");
    SetTargetFPS(60);

    Director::GetInstance().TransitionTo(RENDER_STATE::MAIN);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Director::GetInstance().Draw();
        EndDrawing();
        Director::GetInstance().Update();
    }
    Director::GetInstance().TransitionTo(RENDER_STATE::WAITING);

    return 0;
    
}

