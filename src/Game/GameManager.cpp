#include <iostream>
#include "GameManager.h"

extern Texture2D* Map;
extern Texture2D* Frieren;
extern Texture2D* Fern;
extern Texture2D* Leaves;
int State1 = 0;
int State2 = 0;
int State3 = 0;

GameManager& GameManager::GetInstance()
{
    static GameManager Instance;
    return Instance;
}

const size_t &GameManager::GetTime() const
{
    return Clock;
}

const Vector2* GameManager::GetWayPointList() const
{
    return WayPointList;
}

const size_t& GameManager::GetWayPointSize() const
{
    return WayPointSize;
}

Enemy ** GameManager::GetEnemyList() const
{
    return EnemyList;
}

Tower ** GameManager::GetTowerList() const
{
    return TowerList;
}
void GameManager::Draw() const
{
    Vector2 mousePos = GetMousePosition();
    DrawTexturePro(*Map, { 0.0f, 0.0f, 800.0f, 480.0f }, { 0.0f, 0.0f, 1600.0f, 960.0f }, { 0.0f, 0.0f }, 0.0f, WHITE);
    // DrawTexturePro(*Frieren, { State1 * 64.0f, 0.0f, 64.0f, 64.0f }, { 560.0f, 435.0f, 128.0f, 128.0f }, {0.0f, 0.0f}, 0.0f, WHITE);
    DrawTexturePro(*Fern, { State2 * 64.0f, 0.0f, 64.0f, 64.0f }, { 297.0f, 591.0f, 128.0f, 128.0f }, {0.0f, 0.0f}, 0.0f, WHITE);
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (EnemyList[i]->GetEnemyType() != ENEMY_TYPE::ENEMY_NONE)
        {
            EnemyList[i]->Draw();
        }
    }
    
    for (size_t i = 0; i < MAX_TOWER; i++)
    {
        if (TowerList[i]->GetTowerType() != TOWER_TYPE::TOWER_NONE)
        {
            TowerList[i]->Draw();
        }
    }
    

    for (int i = 0; i < MAX_ATTACK; i++)
    {
        if (AttackList[i]->GetAttackType() != ATTACK_TYPE::ATTACK_NONE)
        {
            AttackList[i]->Draw();
        }
    }
    DrawText(TextFormat("Mouse Position: [%.0f, %.0f]", mousePos.x, mousePos.y), 10, 10, 20, WHITE);
}

bool GameManager::AddEnemy(const ENEMY_TYPE& __Type)
{
    for (size_t i = 0; i < MAX_ENEMY; i++)
    {
        if (EnemyList[i]->GetEnemyType() == ENEMY_TYPE::ENEMY_NONE)
        {
            EnemyList[i]->SetStartWayPoint(WayPointList[0]);
            EnemyList[i]->SetEndWayPoint(WayPointList[1]);
            EnemyList[i]->SetEnemyPosition(WayPointList[0]);
            EnemyList[i]->SetCurrentWayPoint(0);
            EnemyList[i]->SetHealth(800);
            EnemyList[i]->SetType(ENEMY_TYPE::ZOMBIE);
            return true;
        }
    }
    return false;
}

bool GameManager::AddAttack(const Vector2 &__StartPosition, const Vector2 &__ArrivePosition, const ATTACK_TYPE& __Type, const size_t& __EnemyID, const size_t& __TowerID)
{
    for (size_t i = 0; i < MAX_ATTACK; i++)
    {
        if (AttackList[i]->GetAttackType() == ATTACK_TYPE::ATTACK_NONE)
        {
            std::cout << "Add an attack to EnemyID : " << __EnemyID << std::endl;
            AttackList[i]->SetTowerID(__TowerID);
            AttackList[i]->SetTargetEnemy(__EnemyID);
            AttackList[i]->SetShootTime(0);
            AttackList[i]->SetAttackType(__Type);
            AttackList[i]->SetAttackStartPosition(__StartPosition);
            AttackList[i]->SetAttackArrivePostion(__ArrivePosition);
            return true;
        }
    }
    
    return false;
}

void GameManager::Update()
{
    if (Clock > static_cast<size_t>(10e10))
    {
        Clock = 0;
    }

    if (Clock % 300 == 0)
    {
        GameManager::GetInstance().AddEnemy(ZOMBIE);
    }

    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (EnemyList[i]->GetEnemyType() != ENEMY_TYPE::ENEMY_NONE)
        {
            EnemyList[i]->Update();
        }
    }

    for (size_t i = 0; i < MAX_TOWER; i++)
    {
        if (TowerList[i]->GetTowerType() != TOWER_TYPE::TOWER_NONE)
        {
            TowerList[i]->Update();
        }
    }

    for (int i = 0; i < MAX_ATTACK; i++)
    {
        if (AttackList[i]->GetAttackType() != ATTACK_TYPE::ATTACK_NONE)
        {
            AttackList[i]->Update();
        }
    }

    Clock++;
}

GameManager::~GameManager()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        delete EnemyList[i];
    }

    delete[] EnemyList;
}
