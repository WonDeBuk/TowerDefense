#pragma once

#include <math.h>
#include <raylib.h>

enum ENEMY_TYPE
{
    ZOMBIE,
    ENEMY_NONE
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
        ENEMY_TYPE Type;
    public:
        Enemy();

        const ENEMY_TYPE& GetEnemyType() const;
        const Vector2& GetEnemyPosition() const;
        const size_t& GetHealth() const;
        void SetEnemyPosition(const Vector2&);
        void SetStartWayPoint(const Vector2&);
        void SetEndWayPoint(const Vector2&);
        void SetCurrentWayPoint(const size_t&);
        void SetType(const ENEMY_TYPE&);
        void SetHealth(const size_t&);
        void AddDamage(const size_t&);
        void Draw() const;
        void DrawHealth() const;
        void Update();
};