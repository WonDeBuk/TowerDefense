#include "Game/Enemy.h"
#include "Game/GameManager.h"
#include <cmath>
#include <raylib.h>
#include <iostream>

extern Texture2D* ZombieTexture;

Enemy::Enemy() : AnimationState(0), EnemyPosition({0.0f, 0.0f}), EnemyFuturePosition({0.0f, 0.0f}), StartWayPoint({0.0f, 0.0f}), EndWayPoint({0.0f, 0.0f}), SpawnTime(0), CurrentWayPoint(1), Type(NONE)
{
}

const EnemyType &Enemy::GetEnemyType() const
{
    return Type;
}

void Enemy::SetEnemyPosition(const Vector2& __Position)
{
    EnemyPosition = __Position;
    float DeltaX = EndWayPoint.x - StartWayPoint.x;
    float DeltaY = EndWayPoint.y - StartWayPoint.y;
    Angle = atan2f(DeltaY, DeltaX);
    EnemyFuturePosition.x = EnemyPosition.x + 0.5f * cos(Angle);
    EnemyFuturePosition.y = EnemyPosition.y + 0.5f * sin(Angle);
}

void Enemy::SetStartWayPoint(const Vector2& __WayPoint)
{
    StartWayPoint = __WayPoint;
}

void Enemy::SetEndWayPoint(const Vector2& __WayPoint)
{
    EndWayPoint = __WayPoint;
}

void Enemy::SetType(const EnemyType& __Type)
{
    Type = __Type;
}

void Enemy::SetCurrentWayPoint(const size_t& __CurrentWayPoint)
{
    CurrentWayPoint = __CurrentWayPoint;
}

void Enemy::Draw() const
{
    if (Type == ZOMBIE)
    {
        DrawTexturePro(*ZombieTexture, {AnimationState * 32.0f, AnimationState / 3 * 32.0f, 32.0f, 32.0f}, {EnemyPosition.x - 32.0f, EnemyPosition.y - 32.0f, 64.0f, 64.0f}, {0.0f, 0.0f}, 0.0f, WHITE);
    }
}

void Enemy::Update()
{
    if (Type == NONE)
    {
        return;
    }

    if (SpawnTime % 10 == 0)
    {
        AnimationState++;
        AnimationState %= 3;
        if (PI / 2 - abs(Angle) < 0.01f)
        {
            AnimationState += 3;
        }
        SpawnTime = 0;
    }

    float DifferenceFutureEnd = sqrt((EnemyFuturePosition.x - EndWayPoint.x) * (EnemyFuturePosition.x - EndWayPoint.x) +
                                        (EnemyFuturePosition.y - EndWayPoint.y) * (EnemyFuturePosition.y - EndWayPoint.y));
    if (DifferenceFutureEnd - 0.5f > 0.01f)
    {
        EnemyPosition = EnemyFuturePosition;
    }
    else
    {
        ++CurrentWayPoint;
        EnemyPosition = EndWayPoint;
        if (CurrentWayPoint == GameManager::GetInstance().WayPointSize)
        {
            Type = NONE;
            AnimationState = 0;
            SpawnTime = 0;
            return;
        }
        StartWayPoint = EndWayPoint;
        EndWayPoint = GameManager::GetInstance().GetWayPointList()[CurrentWayPoint];
        float DeltaX = EndWayPoint.x - StartWayPoint.x;
        float DeltaY = EndWayPoint.y - StartWayPoint.y;
        Angle = atan2f(DeltaY, DeltaX);
    }

    EnemyFuturePosition.x = EnemyPosition.x + 0.5f * cos(Angle);
    EnemyFuturePosition.y = EnemyPosition.y + 0.5f * sin(Angle);

    SpawnTime++;
}