#include "Game/Enemy.h"
#include "Game/GameManager.h"
#include <cmath>
#include <iostream>
#include <raymath.h>

float GetRandomFloat(float min, float max) {
    return min + ((float)GetRandomValue(0, 100) / 100.0f) * (max - min);
}

Enemy::Enemy() : SpawnOffsetX(GetRandomFloat(-20.0f, 20.0f)), SpawnOffsetY(GetRandomFloat(-20.0f, 20.0f)) {
    FrameTime = 0;
    ID = -1;
}

void Enemy::SetID(const size_t& _id) {
    if (_id >= 0 && _id < MAX_ENEMY)
        ID = _id;
}

void Enemy::SetPosition(const Vector2& _pos) {
    CurrentPosition.x = _pos.x + SpawnOffsetX;
    CurrentPosition.y = _pos.y + SpawnOffsetY;
    NextPosition = CurrentPosition;
}

void Enemy::Update()
{
    GameManager& GameM = GameManager::GetInstance();
    
    if (CurrentPosition.x == GameM.GetWayPointList()[WaypointIndex].x + SpawnOffsetX &&
        CurrentPosition.y == GameM.GetWayPointList()[WaypointIndex].y + SpawnOffsetY) {
        WaypointIndex++;
        if (WaypointIndex == GameM.GetWayPointSize())
        {
            Die();
            return;
        }
        Direction = Vector2Normalize(Vector2Subtract(GameM.GetWayPointList()[WaypointIndex], GameM.GetWayPointList()[WaypointIndex - 1]));
        //recalculating direction the enemy faces
        float Angle = atan2f(Direction.y, Direction.x);
        if (Angle > -PI / 4 && Angle <= PI / 4) AnimationState = 0; //left
        else if (Angle > PI / 4 && Angle <= PI * 3 / 4) AnimationState = 1; //up
        else if (Angle > PI * 3 / 4 || Angle <= -PI * 3 / 4) AnimationState = 0; //right
        else AnimationState = 1; //down

        NextPosition.x = CurrentPosition.x + Speed * Direction.x / GetFPS();
        NextPosition.y = CurrentPosition.y + Speed * Direction.y / GetFPS();
    }

    Vector2 OffsetWayPoint = { GameM.GetWayPointList()[WaypointIndex].x + SpawnOffsetX, GameM.GetWayPointList()[WaypointIndex].y + SpawnOffsetY};
    float SqrDistance = Vector2DistanceSqr(NextPosition, OffsetWayPoint);
    if (SqrDistance <= powf(Speed / GetFPS(), 2)) {
        CurrentPosition = NextPosition;
        NextPosition = OffsetWayPoint;
    }
    else {
        CurrentPosition = NextPosition;
        NextPosition.x = CurrentPosition.x + Speed * Direction.x / GetFPS();
        NextPosition.y = CurrentPosition.y + Speed * Direction.y / GetFPS();
    }
}

void Enemy::OnDamaged(const size_t& _damage)
{
    if (Health <= _damage)
    {
        Die();
        return;
    }

    Health -= _damage;
}

void Enemy::OnDeath()
{
    GameManager::GetInstance().AddCash(CashDrop);
}

void Enemy::Die()
{
    if (Health == 0) OnDeath();
    GameManager::GetInstance().DeallocateEnemy(ID);

}
/*
Enemy::Enemy() : Angle(0.0f), Health(0), AnimationState(0), EnemyPosition({0.0f, 0.0f}), EnemyFuturePosition({0.0f, 0.0f}), StartWayPoint({0.0f, 0.0f}), EndWayPoint({0.0f, 0.0f}), SpawnTime(0), CurrentWayPoint(1), Type(ENEMY_TYPE::ENEMY_NONE)
{
}

const ENEMY_TYPE &Enemy::GetEnemyType() const
{
    return Type;
}

const Vector2& Enemy::GetEnemyPosition() const
{
    return EnemyPosition;
}

const size_t &Enemy::GetHealth() const
{
    return Health;
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

void Enemy::SetType(const ENEMY_TYPE& __Type)
{
    Type = __Type;
}

void Enemy::SetHealth(const size_t& __Health)
{
    Health = __Health;
}

void Enemy::AddDamage(const size_t& __Damage)
{
    if (__Damage >= Health)
    {
        Type = ENEMY_TYPE::ENEMY_NONE;
        AnimationState = 0;
        SpawnTime = 0;
    }
    else
    {
        Health -= __Damage;
    }
}

void Enemy::SetCurrentWayPoint(const size_t& __CurrentWayPoint)
{
    CurrentWayPoint = __CurrentWayPoint;
}

void Enemy::Draw() const
{
    if (Type == ENEMY_TYPE::ZOMBIE)
    {
        // DrawRectangleLinesEx({(int) EnemyPosition.x - 24.0f, (int) EnemyPosition.y - 24.0f, 48.0f, 48.0f}, 1.0f, WHITE);
        DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Slime.png"), {AnimationState * 32.0f, AnimationState / 3 * 32.0f, 32.0f, 32.0f}, {(int) EnemyPosition.x - 24.0f, (int) EnemyPosition.y - 24.0f, 48.0f, 48.0f}, {0.0f, 0.0f}, 0.0f, WHITE);
        DrawHealth();
    }
}

void Enemy::DrawHealth() const
{
    if (Type == ENEMY_TYPE::ENEMY_NONE)
    {
        return;
    }

    DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/HealthBar.png"), {(5 - static_cast<size_t>((float) Health / ((float) 800 / 5))) * 48.0f, 0.0f, 48.0f, 16.0f}, { (int) EnemyPosition.x - 32.0f,(int) EnemyPosition.y - 36.0f, 64.0f, 16.0f }, {0.0f, 0.0f}, 0.0f, WHITE);
}

void Enemy::Update()
{
    if (Type == ENEMY_TYPE::ENEMY_NONE)
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
        if (CurrentWayPoint == GameManager::GetInstance().GetWayPointSize())
        {
            Type = ENEMY_TYPE::ENEMY_NONE;
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
*/