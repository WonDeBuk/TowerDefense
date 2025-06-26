#include "PlayState.h"

PlayState::PlayState()
{
    ForestMap = { 500.0f, 500.0f, 200.0f, 100.0f};
    StateTitle = "Play State";
    BackButton = { 10.0f, 10.0f, 100.0f, 50.0f };
}

void PlayState::Update()
{
    Vector2 MousePosition = GetMousePosition();

    if (CheckCollisionPointRec(MousePosition, ForestMap)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Director::GetInstance().TransitionTo(RENDER_STATE::GAME);
        }
    }
    if (CheckCollisionPointRec(MousePosition, BackButton)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Director::GetInstance().TransitionTo(RENDER_STATE::MAIN);
        }
    }
}

void PlayState::Draw() const
{
    DrawRectangleRec(ForestMap, GREEN);
    DrawText("Forest Map", ForestMap.x + 10, ForestMap.y + 10, 20, WHITE);
    DrawText(StateTitle.c_str(), 10, GetScreenHeight() - 20, 20, WHITE);
    DrawRectangleRec(BackButton, GRAY);
    DrawText("Back", BackButton.x + 10, BackButton.y + 10, 20, WHITE);
}
