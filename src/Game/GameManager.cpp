#include "GameManager.h"
#include "WaveManager.h"
#include <thread>
#include <string>
#include <iostream>

GameManager::~GameManager() {
    for (size_t i = 0; i < MAX_ENEMY; i++) {
        if (EnemyUsed[i] == true)
            DeallocateEnemy(i);
    }
}

GameManager& GameManager::GetInstance()
{
    static GameManager Instance;
    return Instance;
}

const Vector2* GameManager::GetWayPointList() const
{
    return WayPointList;
}

const size_t& GameManager::GetWayPointSize() const
{
    return WayPointSize;
}

const char(&GameManager::GetEnemyList() const)[MAX_ENEMY][sizeof(Enemy)] {
    return EnemyList;
}

const bool(&GameManager::GetEnemyUsed() const)[MAX_ENEMY] {
    return EnemyUsed;
}

void GameManager::Draw()
{
    Vector2 mousePos = GetMousePosition();
    DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Map.png"), { 0.0f, 0.0f, 800.0f, 480.0f }, { 0.0f, 0.0f, 1600.0f, 960.0f }, { 0.0f, 0.0f }, 0.0f, WHITE);

    for (size_t i = 0; i < MAX_ENEMY; i++) {
        if (EnemyUsed[i] == true) {
            reinterpret_cast<Enemy*>(EnemyList[i])->Draw();
        }
    }
    WaveManager::GetInstance().Draw();
    DrawText(TextFormat("Mouse Position: [%.0f, %.0f]", mousePos.x, mousePos.y), 10, 10, 20, WHITE);
}

void GameManager::AddEnemy(const EnemyType& __Type)
{
    Enemy* obj = AllocateEnemy(__Type);
    if (obj != nullptr) {
        TotalEnemy++;
        obj->SetPosition({ WayPointList[0] });
    }
}

void GameManager::UpdateEnemy() {
    for (size_t i = 0; i < MAX_ENEMY; i++) {
        if (EnemyUsed[i] == true) {
            reinterpret_cast<Enemy*>(EnemyList[i])->Update();
        }
    }
}

void GameManager::Update()
{   
    //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) AddEnemy(ENEMY_SLIME);

    UpdateEnemy();
    WaveManager::GetInstance().Update();
}

void GameManager::AddCash(const size_t& _cash)
{
    Cash += _cash;
}

Enemy* GameManager::AllocateEnemy(const EnemyType& _type) {
    for (size_t i = 0; i < MAX_ENEMY; i++) {
        if (EnemyUsed[i] == false) {
            EnemyUsed[i] = true;
            Enemy* obj = nullptr;
            switch (_type) {
            case ENEMY_SLIME:
                obj = new (EnemyList[i]) SlimeEnemy;
                obj->SetID(i);
                break;
            }
            return obj;
        }
    }
    return nullptr;
}

void GameManager::DeallocateEnemy(const size_t& _id) {
    if (EnemyUsed[_id] == false) return;
    TotalEnemy--;
    EnemyUsed[_id] = false;
    reinterpret_cast<Enemy*>(EnemyList[_id])->~Enemy();
}

const size_t& GameManager::GetTotalEnemy() const {
    return TotalEnemy;
}

void GameManager::ChangeLayoutConfig(const WaveLayoutType& _type) {
    switch (_type) {
    case WAVE_LAYOUT_FOREST:
        WaveManager::GetInstance().SetLayout(LayoutConfig[0]);
        break;
    default:
        WaveManager::GetInstance().SetLayout(LayoutConfig[0]);
    }
   
}