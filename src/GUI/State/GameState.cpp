#include "GameState.h"
#include "././Utils/Define.h"
#include "raymath.h"
#include "././Game/GameManager.h"
#include "././Game/Attack/Projectile.h"
#include "././Game/Attack/Missile.h"
#include "././Game/WaveManager.h"

#include "Game/VisualManager.h"
#include "Utils/ResourceManager.h"
#include "Utils/Champion.h"
#include "GUI/Director.h"
#include <iostream>

GameState::GameState() {
    SelectedTower = -1;

}

void GameState::Update() {
    GameManager::GetInstance().Update();
    WaveManager::Update();
    
    int Key = GetKeyPressed();
    if (Key) {
        switch (Key) {
        case KEY_ONE:
            SelectedTower = (int)ChampionType::FERN;
            break;
        case KEY_TWO:
            SelectedTower = (int)ChampionType::FRIEREN;
            break;
        case KEY_THREE:
            SelectedTower = (int)ChampionType::MILIM;
            break;
        case KEY_FOUR:
            SelectedTower = (int)ChampionType::RIMURU;
            break;
        case KEY_FIVE:
            SelectedTower = (int)ChampionType::SHUNA;
            break;
        case KEY_SIX:
            SelectedTower = (int)ChampionType::STARK;
            break;
        default:
            SelectedTower = -1;
            break;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {        
        const bool(&TowerPoolAndPlotTracker)[MAX_TOWER_AMOUNT] = GameManager::GetInstance().GetTowerPlotAndPoolTracker();
        for (int i = 0; i < GameManager::GetInstance().GetTowerPlotSize(); i++) {
            if (CheckCollisionPointCircle(GetMousePosition(), GameManager::GetInstance().GetTowerPlotByID(i), 32)) {
                if (TowerPoolAndPlotTracker[i]) GameManager::GetInstance().GetTowerByID(i)->OnUpgrade();
                else if (SelectedTower != -1 && !TowerPoolAndPlotTracker[i]) GameManager::GetInstance().AddTower((ChampionType)SelectedTower, i);
                SelectedTower = -1;
                break;
            }
        }
    }
}

void GameState::Draw() const {
    GameManager::GetInstance().Draw();
    if (SelectedTower != -1) {
        DrawText(ResourceManager::GetInstance().ParseChampionTypeToString[SelectedTower].c_str(), 100, 100, 32, BLACK);
        ResourceManager::GetInstance().ChampionDataList[SelectedTower].ChampionDraw(ChampionAnimationState::IDLE, GetMousePosition(), false, Director::GetInstance().GetTime());
    }
    else DrawText("No tower is selected!", 100, 100, 32, BLACK);
}
