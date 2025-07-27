#pragma once

#include <raylib.h>
#include <string>

#define MAX_ENEMY_AMOUNT 100
#define MAX_ENEMY_SIZE 200

#define MAX_ATTACK_AMOUNT 100
#define MAX_ATTACK_SIZE 200

#define MAX_TOWER_AMOUNT 10
#define MAX_TOWER_SIZE 200

#define MAX_WAYPOINT_AMOUNT 20

#define MAX_SPAWN_PER_PHASE 5
#define MAX_PHASE_PER_WAVE 3
#define MAX_WAVE 5

#define MAP_WIDTH 50
#define MAP_HEIGHT 30

#define CHAMPION_FRAME_AMOUNT 10
#define CHAMPION_TEXTURE_SIZE 160.0f
#define CHAMPION_TEXTURE_Y_OFFSET 128.0f
#define CHAMPION_TEXTURE_DRAW_SIZE 320.0f

#define MAX_VISUAL_AMOUNT 100
#define MAX_VISUAL_SIZE 75

#define BLACK_LIST_SIZE 5
#define BLACK_LIST_TIME 30

enum class MapType {
    FOREST, FROZEN, DESERT, COUNTING
};

enum class EnemyType {
    SLIME, DINO, BAT, DRAGON,
    FROST, GOLEM, GRUMBLE, TITAN, 
    MAGMA, BANDIT, SCOUT, REVENANT,
    GHOUL, HEALBOT, HORNET, PEST, BRAWLER,
    COUNTING
};

enum class HitType {
    TARGETED, AIMLESS, OVERRIDE, PRESERVE
};

enum class TargetType {
    FIRST, LAST, WEAKEST, STRONGEST
};

enum class AttackType {
    PROJECTILE, MISSILE, ORBIT, RICOCHET, AREA, SPLIT, COUNTING
};

enum class Language {
    ENGLISH, VIETNAMESE, DUTCH, FRENCH, ITALIAN, SPANISH, PORTUGUESE, RUSSIAN, INDONESIAN, COUNTING
};

enum GameStatePeriod {
    WAVE, BUILD, RESUME, WIN, LOSE
};

enum class ChampionTierType {
    COMMON, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC, COUNTING
};

enum class ChampionType {
    FRIEREN, RIMURU, MILIM, STARK, FERN, SHUNA, DAI, LINA, GOURRY, MAAM, XELLOS, POPP, COUNTING
};

// enum class ChampionType {
//     FRIEREN, FERN, STARK, RIMURU, MILIM, SHUNA, DAI, POPP, LINA, GOURRY, MAAM, XELLOS, COUNTING
// };

// enum class ChampionAnimationState {
//     IDLE, FIRST_CAST, SECOND_CAST, THIRD_CAST, COUNTING
// };

enum class ChampionAnimationState {
    IDLE, CAST, COUNTING
};

enum class VisualType {
    PLAIN, TOWER_BIND, ENEMY_BIND, COUNTING
};

typedef struct TextureData {
    float ScaleFactor;
    int MaxFrameCount;
    Texture2D* LinkedTexture;
} TextureData;

typedef struct BlackListData {
    int EnemyID = -1;
    int TimeAdded;
} BlackListData;

typedef struct EnemyData {
    std::string StringName;
    float BaseHealth;
    float BaseSpeed;
    float BaseCash;
} EnemyData;

typedef struct SpawnData {
    EnemyType SpawnEnemyType;
    int SpawnTime;
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