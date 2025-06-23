#pragma once

#include "Game/Enemy.h"
#include <raylib.h>
#include <math.h>
#include <string>

enum ATTACK_TYPE
{
    ATTACK_NONE,
    ZOLTRAAK
};

class Attack
{
    private:
        Vector2 AttackStartPosition;
        Vector2 AttackArrivePosition;
        ATTACK_TYPE AttackType;
        size_t TowerID;
        size_t ShootTime;
        size_t TargetEnemy;
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