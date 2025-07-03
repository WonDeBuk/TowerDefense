#pragma once

#include "Game/Enemy.h"
#include <raylib.h>
#include <math.h>
#include <string>
#include <vector>

enum AttackType {
    ATTACK_BULLET,
    ATTACK_NONE,
    ZOLTRAAK,
    PROJECTILE,
    MISSILE
};

class Attack {
protected:
    AttackType Type;

    size_t Damage;
    size_t Speed;
    
    Vector2 Origin;
    Vector2 Destination;
    double Lifespan;

    size_t ID;
public:
    Attack();
    virtual ~Attack();

    virtual void SetID(const size_t&);
    virtual void SetOrigin(const Vector2&);
    virtual void SetDestination(const Vector2&);
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void OnExpired() = 0;
    virtual void Die();
};

/*
class Attack
{
    protected:
        std::vector<Vector2> AttackPath;
        Vector2 AttackStartPosition;
        Vector2 AttackArrivePosition;
        ATTACK_TYPE AttackType;
        size_t TowerID;
        size_t ShootTime;
        size_t TargetEnemy;

        size_t ID;
    public:
        Attack();

        const ATTACK_TYPE& GetAttackType() const;
        const size_t& GetTowerID() const;

        void SetAttackStartPosition(const Vector2&);
        void SetAttackArrivePostion(const Vector2&);
        void SetAttackType(const ATTACK_TYPE&);
        void SetShootTime(const size_t&);
        void SetTargetEnemy(const size_t&);
        void SetTowerID(const size_t&);

        void Update();
        void Draw() const;
};
*/