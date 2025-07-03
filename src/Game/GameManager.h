#pragma once

#include "Utils/AssetManager.h"
#include "Enemy.h"
#include "Attack.h"
#include "Tower.h"
#include "Enemy/SlimeEnemy.h"
#include <new>
#include <raylib.h>

#define MAX_ENEMY 100
#define MAX_ATTACK 100
#define MAX_TOWER 10
#define MAX_WAYPOINT 20
#define ENEMY_SPAWN_TIME 100
#define MAP_WIDTH 50
#define MAP_HEIGHT 30
class Attack;

class GameManager
{
private:
    char EnemyList[MAX_ENEMY][sizeof(Enemy)];
    bool EnemyUsed[MAX_ENEMY] = { false };
    size_t TotalEnemy;

    char AttackList[MAX_ATTACK][sizeof(Attack)];
    bool AttackUsed[MAX_ATTACK] = { false };
    
    Vector2* WayPointList;
    size_t WayPointSize;
    size_t Cash;
    size_t Timer;

    GameManager()
    {        
        TotalEnemy = 0;
        Timer = 120;
        WayPointList = new Vector2[MAX_WAYPOINT];
        WayPointSize = 10;

        WayPointList[0] = { 80.0f, 675.0f };
        WayPointList[1] = { 225.0f, 675.0f };
        WayPointList[2] = { 225.0f, 375.0f };
        WayPointList[3] = { 480.0f, 375.0f };
        WayPointList[4] = { 480.0f, 795.0f };
        WayPointList[5] = { 770.0f, 795.0f };
        WayPointList[6] = { 770.0f, 245.0f };
        WayPointList[7] = { 1150.0f, 245.0f };
        WayPointList[8] = { 1150.0f, 535.0f };
        WayPointList[9] = { 1570.0f, 535.0f };
    }
public:
    ~GameManager();

    static GameManager& GetInstance();
    const Vector2* GetWayPointList() const;
    const size_t& GetWayPointSize() const;
    const char(&GetEnemyList() const)[MAX_ENEMY][sizeof(Enemy)];
    const bool(&GetEnemyUsed() const)[MAX_ENEMY];
    const size_t& GetTotalEnemy() const;

    void Draw();
    void AddEnemy(const EnemyType&);
    void UpdateEnemy();
    void Update();
    void AddCash(const size_t&);
    Enemy* AllocateEnemy(const EnemyType&);
    void DeallocateEnemy(const size_t&);
};