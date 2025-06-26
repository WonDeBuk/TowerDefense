#include "Tower.h"
#include "GameManager.h"
#include <iostream>

#include "Attack.h"

extern Texture2D* Frieren;

Tower::Tower() : SpriteState(IDLE), TowerPosition({0.0f, 0.0f}), TowerRange(0), TowerCooldown(0), TowerDamage(0.0f), Type(TOWER_TYPE::TOWER_NONE), TargetEnemy(MAX_ENEMY)
{
}

void Tower::GetLowestEnemy()
{
    Enemy** EnemyList = GameManager::GetInstance().GetEnemyList();
    size_t MinHealth = 10000;
    for (size_t i = 0; i < MAX_ENEMY; i++)
    {
        if (EnemyList[i]->GetEnemyType() != ENEMY_TYPE::ENEMY_NONE)
        {
            Vector2 EnemyPosition = EnemyList[i]->GetEnemyPosition();
            float DeltaX = EnemyPosition.x - TowerPosition.x;
            float DeltaY = EnemyPosition.y - TowerPosition.y;
            if (TowerRange * TowerRange >= DeltaX * DeltaX + DeltaY * DeltaY)
            {
                if (EnemyList[i]->GetHealth() < MinHealth)
                {
                    MinHealth = EnemyList[i]->GetHealth();
                    TargetEnemy = i;
                }
            }
        }
    }
}

const Vector2 &Tower::GetTowerPosition() const
{
    return TowerPosition;
}

const float &Tower::GetTowerRange() const
{
    return TowerRange;
}

const size_t &Tower::GetTowerCooldown() const
{
    return TowerCooldown;
}

const float &Tower::GetTowerDamage() const
{
    return TowerDamage;
}

const TOWER_TYPE &Tower::GetTowerType() const
{
    return Type;
}

void Tower::SetTowerTowerID(const size_t& __TowerID)
{
    TowerID = __TowerID;
}

void Tower::SetTowerSpriteState(const TOWER_SPRITE_STATE& __State)
{
    SpriteState = __State;
}

void Tower::SetTowerPosition(const Vector2& __Position)
{
    TowerPosition = __Position;
}

void Tower::SetTowerType(const TOWER_TYPE& __Type)
{
    Type = __Type;
}

void Tower::SetTowerRange(const float& __Range)
{
    TowerRange = __Range;
}

void Tower::GunUpdate()
{
    if (TowerCooldown == 0)
    {
        GetLowestEnemy();

        if (TargetEnemy == MAX_ENEMY)
        {
            return;
        }

        Enemy** EnemyList = GameManager::GetInstance().GetEnemyList();
        GameManager::GetInstance().AddAttack({TowerPosition.x + 50.0f, TowerPosition.y - 75.0f}, EnemyList[TargetEnemy]->GetEnemyPosition(), ATTACK_TYPE::MISSILE, TargetEnemy, TowerID);
        SpriteState = STAFF_CAST;
        TowerCooldown = 100;
    }
    else
    {
        TowerCooldown--;
    }
}

void Tower::Update()
{
    if (Type == TOWER_TYPE::TOWER_NONE)
    {
        return;
    }

    GunUpdate();
}

void Tower::Draw() const
{
    switch (Type)
    {
    case TOWER_TYPE::FRIEREN:
        switch (SpriteState)
        {
        case IDLE:
            DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Frieren.png"), {((GameManager::GetInstance().GetTime() / 5) % 9) * 64.0f, 0.0f, 64.0f, 80.0f}, {TowerPosition.x - 64.0f, TowerPosition.y - 100.0f, 128.0f, 160.0f}, {0.0f, 0.0f}, 0.0f, WHITE);
            break;
        case STAFF_CAST:
            DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Frieren.png"), {((GameManager::GetInstance().GetTime() / 5) % 9) * 64.0f, 80.0f, 64.0f, 80.0f}, {TowerPosition.x - 64.0f, TowerPosition.y - 100.0f, 128.0f, 160.0f}, {0.0f, 0.0f}, 0.0f, WHITE);
            break;
        default:
            break;
        }
        break;
    
    default:
        break;
    }
    

    //DrawRectanglePro({TowerPosition.x, TowerPosition.y, 8.0f, 8.0f}, {-4.0f, -4.0f}, 0.0f, WHITE);
}