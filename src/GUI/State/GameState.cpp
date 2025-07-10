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
        float Range = 1000.0f;
        Vector2 MousePosition = GetMousePosition();
        Enemy* Found = nullptr;
        float Distance = 0.0f;
        for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
            if (GameManager::GetEnemyPoolTracker()[i]){
                Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
                if (Object != nullptr) {
                    if (Vector2DistanceSqr(Object->GetEnemyCurrentPosition(), MousePosition) <= Range * Range) {
                        if (Found == nullptr || (Found->GetHeaddingWaypointIndex() < Object->GetHeaddingWaypointIndex())) {
                            Found = Object;
                            Distance = Vector2DistanceSqr(GameManager::GetWaypointByIndex(Found->GetHeaddingWaypointIndex()), Found->GetEnemyCurrentPosition());
                        }
                        else if (Found->GetHeaddingWaypointIndex() == Object->GetHeaddingWaypointIndex()) {
                            float ConsideredDistance = Vector2DistanceSqr(GameManager::GetWaypointByIndex(Object->GetHeaddingWaypointIndex()), Object->GetEnemyCurrentPosition());
                            if (ConsideredDistance < Distance) {
                                Distance = ConsideredDistance;
                                Found = Object;
                            }
                        }
                    }
                }
            }
        }
        if (Found != nullptr) {
            float TempAttackMovementSpeed = 8.0f;
            float TempAttackDamage = 10.0f;
            Vector2 EnemyFuturePosition = Found->GetEnemyCurrentPosition();
            float Eta = Vector2Distance(MousePosition, EnemyFuturePosition) / TempAttackMovementSpeed;
            for (int i = 0; i < 8; i++) {
                EnemyFuturePosition = Found->GetEnemyFuturePosition((int) Eta);
                float Eta2 = Vector2Distance(MousePosition, EnemyFuturePosition) / TempAttackMovementSpeed;
                if (fabs(Eta - Eta2) < 0.0f) {
                    break;
                }
                Eta = (Eta2 + Eta) * 0.5f;
            }
            GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(MousePosition, EnemyFuturePosition, TempAttackMovementSpeed, TempAttackDamage, Found->GetEnemyID(), 0));
            GameManager::GetInstance().AddAttack(AttackType::MISSILE, Missile::MissileTemplateBuildAndGet(MousePosition, EnemyFuturePosition, 0.3333f, -0.4f, 0.6666f, 0.4f, TempAttackMovementSpeed, TempAttackDamage, Found->GetEnemyID(), 0));
            GameManager::GetInstance().AddAttack(AttackType::MISSILE, Missile::MissileTemplateBuildAndGet(MousePosition, EnemyFuturePosition, 0.3333f, 0.4f, 0.6666f, -0.4f, TempAttackMovementSpeed, TempAttackDamage, Found->GetEnemyID(), 0));
        }
    }
}

void GameState::Draw() const {
    GameManager::GetInstance().Draw();
}
