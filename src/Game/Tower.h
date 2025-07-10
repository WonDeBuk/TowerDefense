#pragma once

#include "raylib.h"


class Tower
{
private:
    Vector2 TowerPosition;
    float TowerRange;
    size_t TowerCooldown;
    float TowerDamage;
    TowerType Type;
    size_t TargetEnemy;
    size_t TowerID;
public:
    Tower();
    void GetLowestEnemy();
    const Vector2& GetTowerPosition() const;
    const float&  GetTowerRange() const;
    const size_t& GetTowerCooldown() const;
    const float& GetTowerDamage() const;
    const TowerType& GetTowerType() const;
    void SetTowerID(const size_t&);
    void SetTowerPosition(const Vector2&);
    void SetTowerType(const TowerType&);
    void SetTowerRange(const float&);
    void GunUpdate();
    void Update();
    void Draw() const;
};