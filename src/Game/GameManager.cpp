#include "GameManager.h"
#include "WaveManager.h"
#include "Enemy/SlimeEnemy.h"
#include "Enemy/WrathSlimeEnemy.h"
#include "Enemy/SniperSlimeEnemy.h"
#include "Attack/ProjectileAttack.h"
#include <thread>
#include <string>
#include <iostream>

GameManager::~GameManager() {
    for (size_t i = 0; i < MAX_ENEMY; i++) {
        if (EnemyUsed[i] == true)
            DeallocateEnemy(i);
    }

    for (size_t i = 0; i < MAX_ATTACK; i++) {
        if (AttackUsed[i] == true)
            DeallocateAttack(i);
    }
}

GameManager& GameManager::GetInstance() {
    static GameManager Instance;
    return Instance;
}

const Vector2* GameManager::GetWayPointList() const {
    return WayPointList;
}

const size_t& GameManager::GetWayPointSize() const {
    return WayPointSize;
}

char(&GameManager::GetEnemyList())[MAX_ENEMY][136] {
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
            reinterpret_cast<Enemy*>(EnemyList[i])->DrawHealthBar();
        }
    }

    for (size_t i = 0; i < MAX_ATTACK; i++) {
        if (AttackUsed[i] == true) {
            reinterpret_cast<Attack*>(AttackList[i])->Draw();
        }
    }
    WaveManager::GetInstance().Draw();
    DrawText(TextFormat("Mouse Position: [%.0f, %.0f]", mousePos.x, mousePos.y), 10, 10, 20, WHITE);
}

void GameManager::AddEnemy(const EnemyType& __Type) {
    Enemy* obj = AllocateEnemy(__Type);
    if (obj != nullptr) {
        TotalEnemy++;
        obj->SetPosition({ WayPointList[0] });
    }
}

void GameManager::AddAttack(const AttackType& _type, const unsigned int& _dmg, const unsigned int& _spd, const Vector2& _og, const Vector2& _dest) {
    Attack* obj = AllocateAttack(_type, _dmg, _spd);
    if (obj != nullptr) {
        obj->SetDirection(_og, _dest);
    }
}

void GameManager::UpdateEnemy() {
    for (size_t i = 0; i < MAX_ENEMY; i++) {
        if (EnemyUsed[i] == true) {
            reinterpret_cast<Enemy*>(EnemyList[i])->Update();
        }
    }
}

void GameManager::UpdateAttack() {
    for (size_t i = 0; i < MAX_ATTACK; i++) {
        if (AttackUsed[i] == true) {
            reinterpret_cast<Attack*>(AttackList[i])->Update();
        }
    }
}

void GameManager::Update() { 
    Enemy* LowestEnemy = nullptr;
    for (size_t i = 0; i < MAX_ENEMY; i++) {
        if (EnemyUsed[i] == true) {
            Enemy* obj = reinterpret_cast<Enemy*>(EnemyList[i]);
            if (LowestEnemy == nullptr || LowestEnemy->GetHealth() > obj->GetHealth()) LowestEnemy = obj;
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && LowestEnemy && (Timer >= 60)) {
        if (Timer % 10 == 0) AddAttack(ATTACK_PROJECTILE, 40, 250, GetMousePosition(), LowestEnemy->GetPosition());
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            Timer = 0;
        }
    }

    UpdateAttack();
    UpdateEnemy();
    WaveManager::GetInstance().Update();
    Timer++;
}

void GameManager::AddCash(const unsigned int& _cash)
{
    Cash += _cash;
}

Enemy* GameManager::AllocateEnemy(const EnemyType& _type) {
    for (unsigned short i = 0; i < MAX_ENEMY; i++) {
        if (EnemyUsed[i] == false) {
            EnemyUsed[i] = true;
            Enemy* obj = nullptr;
            switch (_type) {
            case ENEMY_SLIME:
                obj = new (EnemyList[i]) SlimeEnemy;
                break;
            case ENEMY_WRATH_SLIME:
                obj = new (EnemyList[i]) WrathSlimeEnemy;
                break;
            case ENEMY_SNIPER_SLIME:
                obj = new (EnemyList[i]) SniperSlimeEnemy;
            }
            obj->SetID(i);
            return obj;
        }
    }
    return nullptr;
}

void GameManager::DeallocateEnemy(const unsigned short& _id) {
    if (EnemyUsed[_id] == false) return;
    TotalEnemy--;
    EnemyUsed[_id] = false;
    reinterpret_cast<Enemy*>(EnemyList[_id])->~Enemy();
}

const size_t& GameManager::GetTotalEnemy() const {
    return TotalEnemy;
}

Attack* GameManager::AllocateAttack(const AttackType& _type, const unsigned short& _dmg, const unsigned short& _spd) {
    for (unsigned short i = 0; i < MAX_ATTACK; i++) {
        if (AttackUsed[i] == false) {
            AttackUsed[i] = true;
            Attack* obj = nullptr;
            switch (_type) {
            case ATTACK_PROJECTILE:
                obj = new (AttackList[i]) ProjectileAttack(_dmg, _spd);
                break;
            }
            obj->SetID(i);
            return obj;
        }
    }


    return nullptr;
}

void GameManager::DeallocateAttack(const unsigned short& _id) {
    if (AttackUsed[_id] == false) return;
    AttackUsed[_id] = false;
    reinterpret_cast<Attack*>(AttackList[_id])->~Attack();
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
