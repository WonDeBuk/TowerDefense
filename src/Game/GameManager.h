#pragma once

#include "Utils/AssetManager.h"

#include "Enemy.h"
#include "Attack.h"
#include "Tower.h"
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
    Enemy** EnemyList;
    Attack** AttackList;
    Tower** TowerList;
    Vector2* WayPointList;
    size_t WayPointSize;
    size_t Clock;

    GameManager()
    {
        Clock = 0;
        EnemyList = new Enemy * [MAX_ENEMY];
        AttackList = new Attack * [MAX_ATTACK];
        TowerList = new Tower * [MAX_TOWER];

        for (size_t i = 0; i < MAX_TOWER; i++)
        {
            TowerList[i] = new Tower;
            TowerList[i]->SetTowerTowerID(i);
        }
        
        for (size_t i = 0; i < MAX_ENEMY; i++)
        {
            EnemyList[i] = new Enemy;
        }

        for (size_t i = 0; i < MAX_ATTACK; i++)
        {
            AttackList[i] = new Attack;
        }
        
        TowerList[0]->SetTowerPosition({625.0f, 520.0f});
        TowerList[0]->SetTowerType(TOWER_TYPE::FRIEREN);
        TowerList[0]->SetTowerRange(200.0f);

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
    static GameManager& GetInstance();
    const size_t& GetTime() const;
    const Vector2* GetWayPointList() const;
    const size_t& GetWayPointSize() const;
    Enemy** GetEnemyList() const;
    Tower** GetTowerList() const;
    void Draw() const;
    bool AddEnemy(const ENEMY_TYPE&);
    bool AddAttack(const Vector2&, const Vector2&, const ATTACK_TYPE&, const size_t&, const size_t&);
    void Update();
    ~GameManager();
};