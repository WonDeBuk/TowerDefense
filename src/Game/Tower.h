#pragma once

#include "raylib.h"
// #include "GameManager.h"  // Remove this include

class GameManager; // Add forward declaration
class Enemy;
class Attack;

enum TOWER_TYPE
{
    TOWER_NONE,
    FRIEREN
};

enum TOWER_SPRITE_STATE
{
    IDLE,
    STAFF_CAST
};

class Tower
{
private:
    Vector2 TowerPosition;
    float TowerRange;
    size_t TowerCooldown;
    float TowerDamage;
    TOWER_TYPE Type;
    size_t TargetEnemy;
    TOWER_SPRITE_STATE SpriteState;
    size_t TowerID;
public:
    Tower();
    void GetLowestEnemy();
    const Vector2& GetTowerPosition() const;
    const float&  GetTowerRange() const;
    const size_t& GetTowerCooldown() const;
    const float& GetTowerDamage() const;
    const TOWER_TYPE& GetTowerType() const;
    void SetTowerTowerID(const size_t&);
    void SetTowerSpriteState(const TOWER_SPRITE_STATE&);
    void SetTowerPosition(const Vector2&);
    void SetTowerType(const TOWER_TYPE&);
    void SetTowerRange(const float&);
    void GunUpdate();
    void Update();
    void Draw() const;
};