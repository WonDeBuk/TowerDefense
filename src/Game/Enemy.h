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
    unsigned int Health; //current health
    unsigned int CashDrop; //money dropped upon death
    float Speed; //current speed
    
    unsigned short WaypointIndex; //the waypoint it is heading to
    Vector2 CurrentPosition; //the position on the path
    Vector2 Direction; //the direction of movement

    Vector2 MemoryPosition; //some kind of anchor for the enemy when it is displaced

    unsigned short FrameTime;
    unsigned short AnimationState; //the kind direction
    unsigned short FrameState; //the animation frame

    unsigned short LifeSpan; //the total time of which the enemy exists
    unsigned short Timer; //something for ability
    float PathTravel; //the total distance the enemy travels

    unsigned short ID; //index number when the enemy is spawned
   
    bool OnTrack; //is enemy following the path
    unsigned short KnockBackFrame;
    float KnockBackForce;
public:
    Enemy();
    virtual ~Enemy();

    virtual Vector2& GetPosition();
    virtual unsigned int& GetHealth();

    virtual void ApplyKnockBack(const float&, const unsigned short&, const Vector2&);

    virtual void CalculateDirection(const Vector2&, const Vector2&);
    virtual void SetID(const unsigned short&);
    virtual void SetPosition(const Vector2&);
    virtual void Update();
    virtual void Draw() = 0;
    virtual void DrawHealthBar() = 0;
    virtual void OnDamaged(const unsigned int&);
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