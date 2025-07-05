#pragma once

#include <raylib.h>

class GameManager;

enum EnemyType {
    ENEMY_NONE,
    ENEMY_SLIME,
    ENEMY_WRATH_SLIME,
    ENEMY_SNIPER_SLIME
};

class Enemy {
public:
    const float SpawnOffsetX;
    const float SpawnOffsetY;
protected:
    size_t Health; //current health
    float Speed; //current speed
    size_t CashDrop; //money dropped upon death
    
    size_t WaypointIndex; //the waypoint it is heading to
    Vector2 CurrentPosition; //the position on the path
    Vector2 NextPosition; //the next position along the path
    Vector2 Direction; //the direction of movement

    size_t FrameTime;
    size_t AnimationState; //the kind direction
    size_t FrameState; //the animation frame

    size_t LifeSpan; //the total time of which the enemy exists
    size_t Timer; //something for ability
    float PathTravel; //the total distance the enemy travels

    size_t ID; //index number when the enemy is spawned
public:
    Enemy();
    virtual ~Enemy();

    virtual Vector2 GetPosition();
    virtual size_t& GetHealth();

    virtual void SetID(const size_t&);
    virtual void SetPosition(const Vector2&);
    virtual void Update();
    virtual void Draw() = 0;
    virtual void DrawHealthBar() = 0;
    virtual void OnDamaged(const size_t&);
    virtual void OnDeath();
    virtual void Die();
};

/*
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
*/