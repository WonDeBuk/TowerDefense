#pragma once

#include <math.h>
#include <raylib.h>

enum EnemyType
{
    ZOMBIE,
    NONE
};

class Enemy
{
    private:
        Vector2 EnemyPosition;
        Vector2 EnemyFuturePosition;
        Vector2 StartWayPoint;
        Vector2 EndWayPoint;
        size_t SpawnTime;
        size_t CurrentWayPoint;
        size_t AnimationState;
        size_t Health;
        float Angle;
        EnemyType Type;
    public:
        Enemy();

        const EnemyType& GetEnemyType() const;
        const Vector2& GetEnemyPosition() const;
        void SetEnemyPosition(const Vector2&);
        void SetStartWayPoint(const Vector2&);
        void SetEndWayPoint(const Vector2&);
        void SetCurrentWayPoint(const size_t&);
        void SetType(const EnemyType&);
        void SetHealth(const size_t&);
        void AddDamage(const size_t&);
        void Draw() const;
        void DrawHealth() const;
        void Update();
};