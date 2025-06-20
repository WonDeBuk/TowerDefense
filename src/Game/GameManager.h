#pragma once

#include "Game/Enemy.h"
#include <raylib.h>

#define MAX_ENEMY 1000
#define MAX_WAYPOINT 20
#define ENEMY_SPAWN_TIME 100
#define MAP_WIDTH 50
#define MAP_HEIGHT 30

class GameManager
{
    private:
        Enemy** EnemyList;
        Vector2* WayPointList;
        size_t Clock;
    
        GameManager()
        {
            Clock = 0;
            EnemyList = new Enemy*[MAX_ENEMY];
            for (size_t i = 0; i < MAX_ENEMY; i++)
            {
                EnemyList[i] = new Enemy;
            }
            
            WayPointList = new Vector2[MAX_WAYPOINT];
            WayPointSize = 6;

            WayPointList[0] = {100.0f, 100.0f};
            WayPointList[1] = {500.0f, 100.0f};
            WayPointList[2] = {500.0f, 500.0f};
            WayPointList[3] = {1000.0f, 500.0f};
            WayPointList[4] = {1000.0f, 100.0f};
            WayPointList[5] = {1500.0f, 100.0f};
        }
    public:
        size_t WayPointSize;
        static GameManager& GetInstance();
        const size_t& GetTime() const;
        const Vector2* GetWayPointList() const;
        void Draw() const;
        bool AddEnemy(const EnemyType&);
        void Update();
        ~GameManager();
};