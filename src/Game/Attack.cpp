#include "Game/Attack.h"
#include "rlgl.h"
#include "Game/GameManager.h"
#include "Attack.h"

#include <iostream>

extern Texture2D* Laser;
extern Texture2D* Aura;

Attack::Attack() : AttackStartPosition({0.0f, 0.0f}), AttackArrivePosition({0.0f, 0.0f}), AttackType(ATTACK_TYPE::ATTACK_NONE), TowerID(0)
{
}

const ATTACK_TYPE &Attack::GetAttackType() const
{
    return AttackType;
}

const size_t &Attack::GetTowerID() const
{
    return TowerID;
}

void Attack::SetAttackStartPosition(const Vector2& __Position)
{
    AttackStartPosition = __Position;
}

void Attack::SetAttackArrivePostion(const Vector2& __Position)
{
    AttackArrivePosition = __Position;
}

void Attack::SetAttackType(const ATTACK_TYPE& __Type)
{
    AttackType = __Type;
}

void Attack::SetShootTime(const size_t& __Time)
{
    ShootTime = __Time;
}

void Attack::SetTargetEnemy(const size_t& __EnemyID)
{
    TargetEnemy = __EnemyID;
}

void Attack::SetTowerID(const size_t& __TowerID)
{
    TowerID = __TowerID;
}

void Attack::Draw() const
{
    size_t Time = GameManager::GetInstance().GetTime();
    switch (AttackType)
    {
    case ATTACK_TYPE::ZOLTRAAK:
        {
            float Distance = sqrt((AttackArrivePosition.x - AttackStartPosition.x) * (AttackArrivePosition.x - AttackStartPosition.x) + (AttackArrivePosition.y - AttackStartPosition.y) * (AttackArrivePosition.y - AttackStartPosition.y));
            float Angle = atan2f(AttackArrivePosition.y - AttackStartPosition.y, AttackArrivePosition.x - AttackStartPosition.x);
            rlPushMatrix();
            rlTranslatef(AttackStartPosition.x, AttackStartPosition.y, 0.0f);
            rlRotatef(Angle * 180.0f / PI, 0.0f, 0.0f, 1.0f);
            //DrawRectangleLinesEx({0.0f, -16.0f, 32.0f, 32.0f}, 1.0f, WHITE);
            //DrawRectangleLinesEx({32.0f, -16.0f, (Distance - 64.0f) * ((float) ShootTime / 100), 32.0f}, 1.0f, WHITE);
            //DrawRectangleLinesEx({(Distance - 64.0f) * ((float) ShootTime / 100) + 32.0f, -16.0f, 32.0f, 32.0f}, 1.0f, WHITE);
            DrawTexturePro(*Aura, {0.0f, 0.0f, 64.0f, 160.0f}, {0.0f, -24.0f, 24.0f, 60.0f}, {0.0f, 8.0f}, 0.0f, WHITE);
            DrawTexturePro(*Laser, {0.0f, (Time / 5 % 8) * 512.0f, 192.0f, 512.0f}, {0.0f, 0.0f, 32.0f, 32.0f}, {0.0f, 16.0f}, 0.0f, WHITE);
            DrawTexturePro(*Laser, {192.0f, (Time / 5 % 8) * 512.0f, 224.0f, 512.0f}, {32.0f, 0.0f, (Distance - 64.0f) * ((float) ShootTime / 40), 32.0f}, {0.0f, 16.0f}, 0.0f, WHITE);
            DrawTexturePro(*Laser, {416.0f, (Time / 5 % 8) * 512.0f, 184.0f, 512.0f}, {(Distance - 64.0f) * ((float) ShootTime / 40) + 32.0f, 0.0f, 32.0f, 32.0f}, {0.0f, 16.0f}, 0.0f, WHITE);
            rlPopMatrix();
        }
        break;
    default:
        break;
    }
}

void Attack::Update()
{
    switch (AttackType)
    {
    case ATTACK_TYPE::ZOLTRAAK:
        {
            Enemy* TargetEnemyPointer = (GameManager::GetInstance().GetEnemyList())[TargetEnemy];
            AttackArrivePosition = TargetEnemyPointer->GetEnemyPosition();
            float Distance = sqrt((AttackArrivePosition.x - AttackStartPosition.x) * (AttackArrivePosition.x - AttackStartPosition.x) + (AttackArrivePosition.y - AttackStartPosition.y) * (AttackArrivePosition.y - AttackStartPosition.y));
            float Angle = atan2f(AttackArrivePosition.y - AttackStartPosition.y, AttackArrivePosition.x - AttackStartPosition.x);
            Vector2 HeadPoint = {cosf(Angle) * (Distance * ((float) ShootTime / 40) + 16.0f) + AttackStartPosition.x, sinf(Angle) * (Distance * ((float) ShootTime / 40) + 16.0f) + AttackStartPosition.y};
            //DrawRectangleLinesEx({TargetEnemyPointer->GetEnemyPosition().x - 24.0f, TargetEnemyPointer->GetEnemyPosition().y - 24.0f, 48.0f, 48.0f}, 1.0f, RED);
            //DrawRectanglePro({HeadPoint.x, HeadPoint.y, 4.0f, 4.0f}, {-2.0f, -2.0f}, 0.0f, RED);
            if (CheckCollisionPointRec(HeadPoint, {TargetEnemyPointer->GetEnemyPosition().x - 24.0f, TargetEnemyPointer->GetEnemyPosition().y - 24.0f, 48.0f, 48.0f}))
            {
                TargetEnemyPointer->AddDamage(50);
                AttackType = ATTACK_TYPE::ATTACK_NONE;
                (GameManager::GetInstance().GetTowerList())[TowerID]->SetTowerSpriteState(TOWER_SPRITE_STATE::IDLE);
            }
        }
        break;
    default:
        break;
    }

    ShootTime++;
}