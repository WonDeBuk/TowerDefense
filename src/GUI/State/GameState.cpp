#include "GameState.h"
#include <iostream>

GameState::GameState()
{
    StateTitle = "Game State";
    BackButton = { 10.0f, 10.0f, 100.0f, 50.0f };
}

void GameState::Update()
{
    GameManager::GetInstance().Update();
    Vector2 MousePosition = GetMousePosition();
    if (CheckCollisionPointRec(MousePosition, BackButton)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Director::GetInstance().TransitionTo(RENDER_STATE::MAIN);
        }
    }
}

void GameState::Draw() const
{
    GameManager::GetInstance().Draw();
    DrawRectangleRec(BackButton, GRAY);
    DrawText("Back", BackButton.x + 10, BackButton.y + 10, 20, WHITE);
}
