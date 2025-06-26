#include "MainState.h"
#include "../Director.h"

MainState::MainState()
{
    StateTitle = "Main Menu";
    Button1 = { 100.0f, 100.0f, 200.0f, 50.0f };
    Button2 = { 100.0f, 200.0f, 200.0f, 50.0f };
    Button3 = { 100.0f, 300.0f, 200.0f, 50.0f };
    Button4 = { 100.0f, 400.0f, 200.0f, 50.0f };
}

void MainState::Update()
{
    Vector2 MousePosition = GetMousePosition();

    if (CheckCollisionPointRec(MousePosition, Button1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Director::GetInstance().TransitionTo(RENDER_STATE::PLAY);
    }
    else if (CheckCollisionPointRec(MousePosition, Button2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Director::GetInstance().TransitionTo(RENDER_STATE::SETTING);
    }
    else if (CheckCollisionPointRec(MousePosition, Button3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Director::GetInstance().TransitionTo(RENDER_STATE::DICTIONARY);
    }
    else if (CheckCollisionPointRec(MousePosition, Button4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Director::GetInstance().TransitionTo(RENDER_STATE::LOAD_GAME);
    }
}

void MainState::Draw() const
{
    DrawRectangleRec(Button1, BLUE);
    DrawText("Play", Button1.x + 50, Button1.y + 15, 20, WHITE);
    
    DrawRectangleRec(Button2, GREEN);
    DrawText("Settings", Button2.x + 30, Button2.y + 15, 20, WHITE);
    
    DrawRectangleRec(Button3, YELLOW);
    DrawText("Dictionary", Button3.x + 20, Button3.y + 15, 20, WHITE);
    
    DrawRectangleRec(Button4, RED);
    DrawText("Load", Button4.x + 70, Button4.y + 15, 20, WHITE);
}
