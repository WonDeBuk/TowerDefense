#pragma once

#include <string>

#define MAX_ENEMY_AMOUNT 100
#define MAX_ENEMY_SIZE 200

#define MAX_ATTACK_AMOUNT 100
#define MAX_ATTACK_SIZE 200

#define MAX_TOWER_AMOUNT 10
#define MAX_TOWER_SIZE 200

#define MAX_WAYPOINT_AMOUNT 20

#define MAX_SPAWN_PER_PHASE 5
#define MAX_PHASE_PER_WAVE 5
#define MAX_WAVE 5

#define MAP_WIDTH 50
#define MAP_HEIGHT 30

enum MapType {
    FOREST, FROZEN, DESERT, COUNTING
};

enum EnemyType {
    SLIME, ENEMYCOUNTING
};

enum AttackType {
    PROJECTILE, MISSILE, ATTACKCOUNTING
};

enum TowerType {
    FRIEREN, TOWERCOUTING
};

enum Language {
    ENGLISH, VIETNAMESE, DUTCH, FRENCH, ITALIAN, SPANISH, PORTUGUESE, RUSSIAN, INDONESIAN, LANGUAGECOUNTING
};

enum ChampionTier {
    COMMON, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC, CHAMPIONTIERCOUNTING
};

enum GameStatePeriod {
    WAVE, BUILD, RESUME, WIN, LOSE
};

typedef struct EnemyData {
    std::string StringName;
    float BaseHealth;
    float BaseSpeed;
    float BaseCash;
} EnemyData;

typedef struct ChampionData {
    std::string ChampionName;
    ChampionTier ChampionTier;
} ChampionData;

typedef struct SpawnData {
    EnemyType SpawnEnemyType;
    int SpawnQuantity;
    int SpawnHasSpawned;
    int SpawnDelay;
} SpawnData;

typedef struct PhaseData {
    SpawnData SpawnList[MAX_SPAWN_PER_PHASE];
    int PhaseSpawnListSize;
    int PhaseHasSpawned;
    int PhaseTotalEnemy;
} PhaseData;

typedef struct WaveData {
    PhaseData PhaseList[MAX_PHASE_PER_WAVE];
    int WavePhaseListSize;
    int WaveCurrentPhase;
    int WaveHasSpawned;
    int WaveTotalEnemy;
} WaveData;