#include "PlayState.h"
#include <././Game/GameManager.h>
#include <././Game/WaveManager.h>

PlayState::PlayState()
{
    ForestMap = { 500.0f, 500.0f, 200.0f, 100.0f};
    BackButton = { 10.0f, 10.0f, 100.0f, 50.0f };
}

void PlayState::Update()
{
    Vector2 MousePosition = GetMousePosition();
    if (CheckCollisionPointRec(MousePosition, ForestMap)) {
        GameManager::GetInstance().ResetConfig();
        GameManager::GetInstance().ReadConfig(MapType::FOREST);
        WaveManager::ResetConfig();
        WaveManager::ReadConfig(MapType::FOREST);
        Director::GetInstance().TransitionTo(RENDER_STATE::GAME);
    }
}

void PlayState::Draw() const
{
    RenderState::Draw();
    DrawRectangleRec(ForestMap, GREEN);
    DrawText("Forest Map", ForestMap.x + 10, ForestMap.y + 10, 20, WHITE);
    DrawRectangleRec(BackButton, GRAY);
    DrawText("Back", BackButton.x + 10, BackButton.y + 10, 20, WHITE);
}
