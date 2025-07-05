#pragma once

#include "Utils/AssetManager.h"
#include "Enemy.h"
#include "Attack.h"
#include "Tower.h"
#include "WaveLayout.h"
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
    char EnemyList[MAX_ENEMY][136];
    bool EnemyUsed[MAX_ENEMY] = { false };
    unsigned short TotalEnemy;

    char AttackList[MAX_ATTACK][80];
    bool AttackUsed[MAX_ATTACK] = { false };
    
    WaveLayout LayoutConfig[4];

    Vector2* WayPointList;
    size_t WayPointSize;
    size_t Cash;
    size_t Timer;

    GameManager()
    {        
        TotalEnemy = 0;
        Timer = 60;
        WayPointList = new Vector2[MAX_WAYPOINT];
        WayPointSize = 10;

        LayoutConfig[0].LoadContent(WAVE_LAYOUT_FOREST);
        LayoutConfig[1].LoadContent(WAVE_LAYOUT_FOREST);
        LayoutConfig[2].LoadContent(WAVE_LAYOUT_FOREST);
        LayoutConfig[3].LoadContent(WAVE_LAYOUT_FOREST);

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
    char(&GetEnemyList())[MAX_ENEMY][136];
    const bool(&GetEnemyUsed() const)[MAX_ENEMY];
    const size_t& GetTotalEnemy() const;

    void ChangeLayoutConfig(const WaveLayoutType&);

    void Draw();
    void AddEnemy(const EnemyType&);
    void AddAttack(const AttackType&, const unsigned int&, const unsigned int&, const Vector2&, const Vector2&);

    void UpdateEnemy();
    void UpdateAttack();
    void Update();
    void AddCash(const unsigned int&);

    Enemy* AllocateEnemy(const EnemyType&);
    void DeallocateEnemy(const unsigned short&);

    Attack* AllocateAttack(const AttackType&, const unsigned short&, const unsigned short&);
    void DeallocateAttack(const unsigned short&);
};