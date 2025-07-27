#include "GameManager.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <new>
#include <queue>
#include <vector>
#include <assert.h>

#include "./Utils/ResourceManager.h"
#include "./Utils/MathUtils.hpp"
#include "Game/VisualManager.h"

#include "Enemy/Slime.h"
#include "Enemy/Dino.h"
#include "Enemy/Bat.h"
#include "Enemy/Dragon.h"
#include "Enemy/Frost.h"
#include "Enemy/Golem.h"
#include "Enemy/Grumble.h"
#include "Enemy/Titan.h"
#include "Enemy/Magma.h"
#include "Enemy/Bandit.h"
#include "Enemy/Scout.h"
#include "Enemy/Revenant.h"
#include "Enemy/Ghoul.h"
#include "Enemy/Healbot.h"
#include "Enemy/Hornet.h"
#include "Enemy/Pest.h"
#include "Enemy/Brawler.h"

#include "Attack/Projectile.h"
//#include "Attack/Missile.h"
#include "Attack/Orbit.h"
#include "Attack/Ricochet.h"
#include "Attack/Area.h"
#include "Attack/Split.h"

#include "Tower/Frieren.h"
#include "Tower/Milim.h"
#include "Tower/Rimuru.h"
#include "Tower/Fern.h"
#include "Tower/Shuna.h"
#include "Tower/Stark.h"

// Khởi tạo các biến static

//delete later
int GameManager::PlayerCash = 100000;

// Các property thuộc về Enemy
char GameManager::EnemyPool[MAX_ENEMY_AMOUNT][MAX_ENEMY_SIZE] = {0};
bool GameManager::EnemyPoolTracker[MAX_ENEMY_AMOUNT] = {false};
int GameManager::CurrentEnemyAmount = 0;
Vector2 GameManager::WaypointList[MAX_WAYPOINT_AMOUNT] = {0.0f, 0.0f};
int GameManager::WaypointSize = 0;

// Các property thuộc về Attack
char GameManager::AttackPool[MAX_ATTACK_AMOUNT][MAX_ATTACK_SIZE] = {0};
bool GameManager::AttackPoolTracker[MAX_ATTACK_AMOUNT] = {false};
int GameManager::CurrentAttackAmount = 0;

// Các property thuộc về Tower
char GameManager::TowerPool[MAX_TOWER_AMOUNT][MAX_TOWER_SIZE] = {0};
Vector2 GameManager::TowerPlotList[MAX_TOWER_AMOUNT] = {0.0f, 0.0f};
bool GameManager::TowerPlotAndPoolTracker[MAX_TOWER_AMOUNT] = {false};
int GameManager::TowerPlotSize = 0;
int GameManager::CurrentTowerAmount = 0;

// Các property khác
MapType GameManager::CurrentMap = MapType::COUNTING;
Texture2D* GameManager::MapTexture = nullptr;
size_t GameManager::Timer = 0;

GameManager::GameManager() {}


// Các method liên quan đến config của game
GameManager& GameManager::GetInstance() {
    static GameManager Instance;
    return Instance;
}

const size_t& GameManager::GetTime() {
    return Timer;
}

const int& GameManager::GetWaypointSize() {
    return WaypointSize;
}

const Vector2& GameManager::GetWaypointByIndex(int _WaypointIndex) {
    return WaypointList[_WaypointIndex];
}

const Vector2(&GameManager::GetWaypointList())[MAX_WAYPOINT_AMOUNT] {
    return WaypointList;
}

const Vector2(&GameManager::GetTowerPlotList())[MAX_TOWER_AMOUNT] {
    return TowerPlotList;
}

const Vector2& GameManager::GetTowerPlotByID(const int& _TowerID) {
    assert((_TowerID >= 0 && _TowerID < TowerPlotSize) && "GameManager * Invalid Tower Plot Get");
    return TowerPlotList[_TowerID];
}

const bool(&GameManager::GetTowerPlotAndPoolTracker())[MAX_TOWER_AMOUNT] {
    return TowerPlotAndPoolTracker;
}

const int& GameManager::GetTowerPlotSize() {
    return TowerPlotSize;
}

const MapType& GameManager::GetCurrentMap() {
    return CurrentMap;
}

void GameManager::ResetConfig() {
    for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
        EnemyPoolTracker[i] = false;
    }
    
    for (int i = 0; i < MAX_ATTACK_AMOUNT; i++) {
        AttackPoolTracker[i] = false;
    }

    for (int i = 0; i < MAX_TOWER_AMOUNT; i++) {
        TowerPlotAndPoolTracker[i] = false;
        TowerPlotList[i] = {0.0f, 0.0f};
    }

    for (int i = 0; i < MAX_WAYPOINT_AMOUNT; i++) {
        WaypointList[i] = {0.0f, 0.0f};
    }

    CurrentEnemyAmount = 0;
    WaypointSize = 0;
    CurrentAttackAmount = 0;
    CurrentTowerAmount = 0;
    TowerPlotSize = 0;
    CurrentMap = MapType::COUNTING;
    MapTexture = nullptr;
    Timer = 0;
}

void GameManager::ChangeConfig(const MapType& _MapType) {
    GameManager::ReadConfig(_MapType);

    CurrentMap = _MapType;
}

void GameManager::ReadConfig(const MapType& _MapType) {
    std::fstream ConfigFile(ResourceManager::GetInstance().GetResourcePath("game/Config_" + ResourceManager::ParseMapTypeToString[(int) _MapType] + ".txt"), std::ios::in);
    MapTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/" + ResourceManager::ParseMapTypeToString[(int)_MapType] + ".png"));
    assert((ConfigFile.is_open()) && "GameManager * Failed To Load Config File");

    std::string LineReadingBuffer;
    bool IsMapConfigFieldFound = false;
    while (!ConfigFile.eof()) {
        std::getline(ConfigFile, LineReadingBuffer);
        if (LineReadingBuffer == "Map Config:") {
            IsMapConfigFieldFound = true;
            break;
        }
    }

    assert(IsMapConfigFieldFound && "GameManager * Failed To Read Map Config Field");

    // Đọc dữ liệu waypoint
    std::getline(ConfigFile, LineReadingBuffer);
    sscanf(LineReadingBuffer.c_str(), "Waypoint Amount: %d", &WaypointSize);
    assert(WaypointSize < MAX_WAYPOINT_AMOUNT && "GameManager * Waypoint Amount Exceed Limit");
    assert(WaypointSize > 0 && "GameManager * Invalid Waypoint Amount");
    for (int i = 0; i < WaypointSize; i++) {
        std::getline(ConfigFile, LineReadingBuffer);
        sscanf(LineReadingBuffer.c_str(), "X: %f, Y: %f", &WaypointList[i].x, &WaypointList[i].y);
    }

    // Đọc dữ liệu tower plot
    std::getline(ConfigFile, LineReadingBuffer);
    sscanf(LineReadingBuffer.c_str(), "Tower Plot Amount: %d", &TowerPlotSize);
    assert(TowerPlotSize < MAX_TOWER_AMOUNT && "GameManager * Tower Plot Amount Exceed Limit");
    assert(TowerPlotSize > 0 && "GameManager * Invalid Tower Plot Amount");
    for (int i = 0; i < TowerPlotSize; i++) {
        std::getline(ConfigFile, LineReadingBuffer);
        sscanf(LineReadingBuffer.c_str(), "X: %f, Y: %f", &TowerPlotList[i].x, &TowerPlotList[i].y);
    }
}

void GameManager::UnitTestPrintData() {
    printf("Current Map Type: %s\n", &ResourceManager::ParseMapTypeToString[(int) CurrentMap][0]);
    printf("Waypoint Amount: %d\n", WaypointSize);
    for (int i = 0; i < WaypointSize; i++) {
        printf("Waypoint %d: X: %f, Y: %f \n", i, WaypointList[i].x, WaypointList[i].y);
    }
    printf("Tower plot Amount: %d\n", TowerPlotSize);
    for (int i = 0; i < TowerPlotSize; i++) {
        printf("Tower Plot %d: X: %f, Y: %f \n", i, TowerPlotList[i].x, TowerPlotList[i].y);
    }
}


// Các method liên quan đến việc sử dụng EnemyPool


const char(&GameManager::GetEnemyPool())[MAX_ENEMY_AMOUNT][MAX_ENEMY_SIZE] {
    return EnemyPool;
}

const bool(&GameManager::GetEnemyPoolTracker())[MAX_ENEMY_AMOUNT] {
    return EnemyPoolTracker;
}

const int& GameManager::GetCurrentEnemyAmount() {
    return CurrentEnemyAmount;
}

Enemy* GameManager::GetEnemyByID(const int& _EnemyID) const {
    assert(_EnemyID < MAX_ENEMY_AMOUNT && "GameManager * Invalid Enemy Get");
    assert(_EnemyID >= 0 && "GameManager * Invalid Enemy Get");
    if (EnemyPoolTracker[_EnemyID]) return reinterpret_cast<Enemy*>(EnemyPool[_EnemyID]);
    return nullptr;
}

void GameManager::AddEnemy(const EnemyType& _EnemyType, const Enemy* _EnemyTemplate) {
    int EmptySlotID = -1;
    for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
        if (EnemyPoolTracker[i] == false) {
            EmptySlotID = i;
            break;
        }
    }

    assert(EmptySlotID < MAX_ENEMY_AMOUNT && "GameManager * Invalid Enemy Add");
    assert(EmptySlotID >= 0 && "GameManager * Invalid Enemy Add");

    Enemy* NewEnemyObject = nullptr;
    if (_EnemyTemplate == nullptr) {
        switch (_EnemyType) {
        case EnemyType::SLIME:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Slime();
            break;
        case EnemyType::DINO:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Dino();
            break;
        case EnemyType::BAT:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Bat();
            break;
        case EnemyType::DRAGON:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Dragon();
            break;
        case EnemyType::FROST:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Frost();
            break;
        case EnemyType::GOLEM:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Golem();
            break;
        case EnemyType::GRUMBLE:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Grumble();
            break;
        case EnemyType::TITAN:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Titan();
            break;
        case EnemyType::MAGMA:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Magma();
            break;
        case EnemyType::BANDIT:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Bandit();
            break;
        case EnemyType::SCOUT:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Scout();
            break;
        case EnemyType::REVENANT:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Revenant();
            break;
        case EnemyType::GHOUL :
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Ghoul();
            break;
        case EnemyType::HEALBOT:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Healbot();
            break;
        case EnemyType::HORNET:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Hornet();
            break;
        case EnemyType::PEST:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Pest();
            break;
        case EnemyType::BRAWLER:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Brawler();
            break;
        default:
            break;
        }
    } else {
        switch (_EnemyType) {
        case EnemyType::SLIME:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Slime(*reinterpret_cast<Slime*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::DINO:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Dino(*reinterpret_cast<Dino*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::BAT:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Bat(*reinterpret_cast<Bat*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::DRAGON:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Dragon(*reinterpret_cast<Dragon*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::BANDIT:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Bandit(*reinterpret_cast<Bandit*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::HORNET:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Hornet(*reinterpret_cast<Hornet*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::PEST:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Pest(*reinterpret_cast<Pest*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::GOLEM:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Golem(*reinterpret_cast<Golem*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::GRUMBLE:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Grumble(*reinterpret_cast<Grumble*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::TITAN:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Titan(*reinterpret_cast<Titan*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::REVENANT:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Revenant(*reinterpret_cast<Revenant*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        case EnemyType::BRAWLER:
            NewEnemyObject = new (EnemyPool[EmptySlotID]) Brawler(*reinterpret_cast<Brawler*>(const_cast<Enemy*>(_EnemyTemplate)));
            break;
        default:
            break;
        }
    }

    assert((NewEnemyObject != nullptr) && "GameManager * Invalid Enemy Constructor");

    EnemyPoolTracker[EmptySlotID] = true;
    NewEnemyObject->SetEnemyID(EmptySlotID);
    CurrentEnemyAmount++;
}

void GameManager::KillEnemy(const int& _EnemyID) {
    assert(_EnemyID < MAX_ENEMY_AMOUNT && "GameManager * Invalid Enemy Kill");
    assert(_EnemyID >= 0 && "GameManager * Invalid Enemy Kill");
    assert(EnemyPoolTracker[_EnemyID] && "GameManager * Invalid Enemy Get");
    EnemyPoolTracker[_EnemyID] = false;
    CurrentEnemyAmount--;
}


// Các method liên quan đến việc sử dụng AttackPool


const char(&GameManager::GetAttackPool())[MAX_ENEMY_AMOUNT][MAX_ATTACK_SIZE] {
    return AttackPool;
}

const bool(&GameManager::GetAttackPoolTracker())[MAX_ENEMY_AMOUNT] {
    return AttackPoolTracker;
}

const int& GameManager::GetCurrentAttackAmount() {
    return CurrentAttackAmount;
}

Attack* GameManager::GetAttackByID(const int& _AttackID) const {
    if (AttackPoolTracker[_AttackID]) return reinterpret_cast<Attack*>(AttackPool[_AttackID]);
    return nullptr;
}

void GameManager::AddAttack(const AttackType& _AttackType, const Attack* _AttackTemplate) {
    int EmptySlotID = -1;
    for (int i = 0; i < MAX_ATTACK_AMOUNT; i++) {
        if (AttackPoolTracker[i] == false) {
            EmptySlotID = i;
            break;
        }
    }

    if (EmptySlotID < 0 || EmptySlotID >= MAX_ATTACK_AMOUNT) return;
    assert(EmptySlotID < MAX_ATTACK_AMOUNT && "GameManager * Invalid Attack Add");
    assert(EmptySlotID >= 0 && "GameManager * Invalid Attack Add");

    Attack* NewAttackObject = nullptr;
    switch (_AttackType) {
        case AttackType::PROJECTILE:
            NewAttackObject = new (AttackPool[EmptySlotID]) Projectile(*reinterpret_cast<Projectile*>(const_cast<Attack*>(_AttackTemplate)));
            break;
        //case AttackType::MISSILE:
        //    NewAttackObject = new (AttackPool[EmptySlotID]) Missile(*reinterpret_cast<Missile*>(const_cast<Attack*>(_AttackTemplate)));
        //    break;
        case AttackType::ORBIT:
            NewAttackObject = new (AttackPool[EmptySlotID]) Orbit(*reinterpret_cast<Orbit*>(const_cast<Attack*>(_AttackTemplate)));
            break;
        case AttackType::RICOCHET:
            NewAttackObject = new (AttackPool[EmptySlotID]) Ricochet(*reinterpret_cast<Ricochet*>(const_cast<Attack*>(_AttackTemplate)));
            break;
        case AttackType::AREA:
            NewAttackObject = new (AttackPool[EmptySlotID]) Area(*reinterpret_cast<Area*>(const_cast<Attack*>(_AttackTemplate)));
            break;
        case AttackType::SPLIT:
            NewAttackObject = new (AttackPool[EmptySlotID]) Split(*reinterpret_cast<Split*>(const_cast<Attack*>(_AttackTemplate)));
            break;
        default:
            break;
    }

    assert((NewAttackObject != nullptr) && "GameManager * Invalid Attack Constructor");

    AttackPoolTracker[EmptySlotID] = true;
    NewAttackObject->SetAttackID(EmptySlotID);
    CurrentAttackAmount++;
}

void GameManager::KillAttack(const int& _AttackID) {
    assert(_AttackID < MAX_ATTACK_AMOUNT && "GameManager * Invalid Attack Kill");
    assert(_AttackID >= 0 && "GameManager * Invalid Attack Kill");
    assert(AttackPoolTracker[_AttackID] && "GameManager * Invalid Attack Get");
    AttackPoolTracker[_AttackID] = false;
    CurrentAttackAmount--;
}


// Các method liên quan đến việc sử dụng TowerPool


 const char(&GameManager::GetTowerPool())[MAX_TOWER_AMOUNT][MAX_TOWER_SIZE] {
     return TowerPool;
 }

 const int& GameManager::GetCurrentTowerAmount() {
     return CurrentTowerAmount;
 }

 Tower* GameManager::GetTowerByID(const int& _TowerID) const {
     if (TowerPlotAndPoolTracker[_TowerID]) return reinterpret_cast<Tower*>(TowerPool[_TowerID]);
     return nullptr;
 }

 void GameManager::AddTower(const ChampionType& _ChampionType, const int& _SlotID) {
     assert(_SlotID < TowerPlotSize && "GameManager * Invalid Tower Add");
     assert(_SlotID >= 0 && "GameManager * Invalid Tower Add");
     assert(!TowerPlotAndPoolTracker[_SlotID] && "GameManager * Invalid Attack Get");

     Tower* NewTowerObject = nullptr;
     switch (_ChampionType) {
         case ChampionType::FRIEREN:
             NewTowerObject = new (TowerPool[_SlotID]) Frieren();
             break;
         case ChampionType::MILIM:
             NewTowerObject = new (TowerPool[_SlotID]) Milim();
             break;
         case ChampionType::RIMURU:
             NewTowerObject = new (TowerPool[_SlotID]) Rimuru();
             break;
         case ChampionType::FERN:
             NewTowerObject = new (TowerPool[_SlotID]) Fern();
             break;
         case ChampionType::SHUNA:
             NewTowerObject = new (TowerPool[_SlotID]) Shuna();
             break;
         case ChampionType::STARK:
             NewTowerObject = new (TowerPool[_SlotID]) Stark();
             break;

         default:
             break;
     }

     assert((NewTowerObject != nullptr) && "GameManager * Invalid TowerConstructor");
     TowerPlotAndPoolTracker[_SlotID] = true;
     NewTowerObject->SetTowerID(_SlotID);
     CurrentTowerAmount++;
 }

 void GameManager::KillTower(const int& _TowerID) {
     assert(_TowerID < MAX_TOWER_AMOUNT && "GameManager * Invalid Tower Kill");
     assert(_TowerID >= 0 && "GameManager * Invalid Tower Kill");
     assert(!TowerPlotAndPoolTracker[_TowerID] && "GameManager * Invalid Tower Get");
     TowerPlotAndPoolTracker[_TowerID] = false;
     CurrentTowerAmount--;
 }


// Draw và Update

static std::priority_queue<std::pair<float,int>, std::vector<std::pair<float,int>>, std::greater<std::pair<float,int>>> DrawLayerYCoorDepend;

void GameManager::Draw() const {
    for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
        if (EnemyPoolTracker[i]) {
            Enemy* EnemyObject = reinterpret_cast<Enemy*>(EnemyPool[i]);
            DrawLayerYCoorDepend.push(std::make_pair(EnemyObject->GetEnemyCurrentPosition().y, i));
        }
    }

    DrawTexturePro(*MapTexture, {0.0f, 0.0f, (float) MapTexture->width, (float) MapTexture->height}, {0.0f, 0.0f, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT}, {0.0f, 0.0f}, 0.0f, WHITE);

    while (!DrawLayerYCoorDepend.empty()) {
        int EnemyDrawID = DrawLayerYCoorDepend.top().second;
        reinterpret_cast<Enemy*>(EnemyPool[EnemyDrawID])->Draw();
        DrawLayerYCoorDepend.pop();
    }   

    for (int i = 0; i < MAX_TOWER_AMOUNT; i++) {
        if (TowerPlotAndPoolTracker[i]) {
            reinterpret_cast<Tower*>(TowerPool[i])->Draw();
        }
    }

    VisualManager::GetInstance().Draw();

    for (int i = 0; i < MAX_ATTACK_AMOUNT; i++) {
        if (AttackPoolTracker[i]) {
            reinterpret_cast<Attack*>(AttackPool[i])->Draw();
        }
    }
        
     DrawText(std::to_string(CurrentAttackAmount).c_str(), 600, 100, 32, BLACK);
}

void GameManager::Update() {
    VisualManager::GetInstance().Update();

    for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
        if (EnemyPoolTracker[i]) {
            reinterpret_cast<Enemy*>(EnemyPool[i])->Update();
        }
    }

     for (int i = 0; i < MAX_ATTACK_AMOUNT; i++) {
         if (AttackPoolTracker[i]) {
             reinterpret_cast<Attack*>(AttackPool[i])->Update();
         }
     }
    
     for (int i = 0; i < MAX_TOWER_AMOUNT; i++) {
         if (TowerPlotAndPoolTracker[i]) {
             reinterpret_cast<Tower*>(TowerPool[i])->Update();
         }
     }

    Timer++;
}


void GameManager::ModifyCash(const int& _ModifyValue) {
    PlayerCash += _ModifyValue;
    if (PlayerCash < 0) PlayerCash = 0;
}