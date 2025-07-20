#include "GameState.h"
#include "././Utils/Define.h"
#include "raymath.h"
#include "././Game/GameManager.h"
#include "././Game/Attack/Projectile.h"
#include "././Game/Attack/Missile.h"
#include "././Game/WaveManager.h"
#include <iostream>

GameState::GameState() {
}

void GameState::Update() {
    GameManager::GetInstance().Update();
    WaveManager::Update();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        float Range = 2000.0f;
        Vector2 MousePosition = GetMousePosition();
        Enemy* Found = nullptr;
        float Distance = 0.0f;
        
        const bool(&TowerPoolAndPlotTracker)[MAX_TOWER_AMOUNT] = GameManager::GetInstance().GetTowerPlotAndPoolTracker();
        for (int i = 0; i < GameManager::GetInstance().GetTowerPlotSize(); i++) {
            if (CheckCollisionPointCircle(GetMousePosition(), GameManager::GetInstance().GetTowerPlotByID(i), 32)) {
                if (TowerPoolAndPlotTracker[i]) GameManager::GetInstance().GetTowerByID(i)->OnUpgrade();
                else GameManager::GetInstance().AddTower(STARK, i);
                break;
            }
        }
    }
}

void GameState::Draw() const {
    GameManager::GetInstance().Draw();
}
