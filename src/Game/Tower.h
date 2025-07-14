#pragma once

#include "raylib.h"

enum TargetType {
    FIRST, LAST, WEAKEST, STRONGEST
};

class Tower {
protected:
    int TowerCooldown;
    int TowerDeltaCooldown;
    int TowerLevel;
    int TotalCost;
    float TowerRange;
    float TowerAttackDamage;
    float TowerAttackMovementSpeed;
    Vector2 TowerPosition;

    int TargetEnemyID;
    int TowerID;                        //identical to TowerPlotID

    size_t TowerLifespan;
    void (Tower::*GetTargetEnemy)();
public:
    Tower();

    virtual const float& GetTowerRange() const { return TowerRange; }
    virtual const int& GetTowerCooldown() const { return TowerCooldown; }
    virtual const int& GetTargetEnemyID() const { return TargetEnemyID; }
    virtual const int& GetTowerID() const { return TowerID; }
    virtual const Vector2& GetTowerPosition() const { return TowerPosition; }

    virtual void SetTargetType(const TargetType& _TargetType);
    virtual void SetTowerID(const int& _ID);
    virtual void SetTowerRange(const float& _TowerRange);

    virtual void GetFirstEnemy();
    virtual void GetLastEnemy();
    virtual void GetWeakestEnemy();
    virtual void GetStrongestEnemy();
    virtual const Vector2 GetEnemyDefinitePosition(const Vector2& _AttackStartPosition) const;

    virtual void Sell() {}                              //implement later...
    virtual void OnUpgrade() = 0;
    virtual void Update() = 0;
    virtual void UpdateAnimation() = 0;
    virtual void Draw() const = 0;
};