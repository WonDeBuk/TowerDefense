#include <Game/GameManager.h>
#include "Game/Enemy.h"

GameManager& GameManager::GetInstance()
{
    static GameManager Instance;
    return Instance;
}

const size_t &GameManager::GetTime() const
{
    return Clock;
}

const Vector2* GameManager::GetWayPointList() const
{
    return WayPointList;
}

void GameManager::Draw() const
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (EnemyList[i]->GetEnemyType() != NONE)
        {
            EnemyList[i]->Draw();
        }
    }
}

bool GameManager::AddEnemy(const EnemyType& __Type)
{
    for (size_t i = 0; i < MAX_ENEMY; i++)
    {
        if (EnemyList[i]->GetEnemyType() == NONE)
        {
            EnemyList[i]->SetStartWayPoint(WayPointList[0]);
            EnemyList[i]->SetEndWayPoint(WayPointList[1]);
            EnemyList[i]->SetEnemyPosition(WayPointList[0]);
            EnemyList[i]->SetCurrentWayPoint(0);
            EnemyList[i]->SetType(ZOMBIE);
            return true;
        }
    }
    
    return false;
}

void GameManager::Update()
{
    if (Clock > static_cast<size_t>(10e10))
    {
        Clock = 0;
    }

    if (Clock % 300 == 0)
    {
        GameManager::GetInstance().AddEnemy(ZOMBIE);
    }

    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (EnemyList[i]->GetEnemyType() != NONE)
        {
            EnemyList[i]->Update();
        }
    }

    Clock++;
}

GameManager::~GameManager()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        delete EnemyList[i];
    }

    delete[] EnemyList;
}
