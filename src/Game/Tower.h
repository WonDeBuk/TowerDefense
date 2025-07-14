#pragma once

#include "raylib.h"


class Tower
{
protected:
    Vector2 TowerPosition;

    int TowerCurrentLevel;
    float TowerRange;
    float TowerDamage;
    int TowerCooldown;

    size_t Lifespan;
public:
    Tower();

    void SetTowerID(const size_t&);

    

    virtual void Update();
    virtual void Draw() const;
    virtual void SetTowerCurrentLevel(const int& __Level);
};