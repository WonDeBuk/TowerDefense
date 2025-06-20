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
        float Angle;
        EnemyType Type;
    public:
        Enemy();

        const EnemyType& GetEnemyType() const;
        void SetEnemyPosition(const Vector2&);
        void SetStartWayPoint(const Vector2&);
        void SetEndWayPoint(const Vector2&);
        void SetCurrentWayPoint(const size_t&);
        void SetType(const EnemyType&);
        void Draw() const;
        void Update();
};