#include "raylib.h"
#include "rlgl.h"

#include "GUI/Director.h"
#include "Utils/ResourceManager.h"
#include "Game/GameManager.h"
#include "Utils/MathUtils.hpp"
#include "Utils/UnicodeText.hpp"

#include <string>
#include <iostream>

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower Defense");
    SetTargetFPS(60);
    Director* MainDirector = &Director::GetInstance();
    MainDirector->Init();
    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        BeginDrawing();
        MainDirector->Draw();
        EndDrawing();
        MainDirector->Update();
    }
}
