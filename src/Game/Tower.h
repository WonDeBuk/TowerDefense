#pragma once

#include "raylib.h"
#include "Utils/Define.h"
#include "Game/VisualManager.h"

class Tower {
protected:
    int TowerCooldown;
    int TowerLevel;
    int TotalCost;
    float TowerRange;
    float TowerAttackDamage;
    float TowerAttackMovementSpeed;
    Vector2 TowerPosition;
    Vector2 AttackPosition;

    int TargetEnemyID;
    int TowerID;                        //identical to TowerPlotID

    ChampionType CurrentChampion;
    ChampionAnimationState CurrentAnimationState;
    size_t TowerLifespan;
    size_t PreviousAttackFrame;
    size_t AttackAnimationFrame;
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
    virtual const Vector2 GetEnemyDefinitePosition(const Vector2& _AttackStartPosition, const int& _TargetEnemyID) const;

    virtual void Sell() {}                              //implement later...
    virtual bool OnUpgrade() = 0;
    virtual void Update() = 0;
    virtual void UpdateAnimation() = 0;
    virtual void Draw() const;
};