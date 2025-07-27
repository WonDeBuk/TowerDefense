#include "WaveManager.h"
#include "../Utils/ResourceManager.h"
#include <fstream>
#include <string>
#include <assert.h>
#include <map>

WaveData WaveManager::WaveList[MAX_WAVE];
int WaveManager::CurrentWaveIndex = 0;
int WaveManager::WaveListSize = 0;
WaveData* WaveManager::CurrentWavePointer = &WaveManager::WaveList[0];
PhaseData* WaveManager::CurrentPhasePointer = &WaveManager::WaveList[0].PhaseList[0];
size_t WaveManager::PhaseTimer = 2000000000;

void WaveManager::ResetConfig() {
    for (int i = 0; i < MAX_WAVE; i++) {
        for (int j = 0; j < MAX_PHASE_PER_WAVE; j++) {
            for (int k = 0; k < MAX_PHASE_PER_WAVE; k++) {
                WaveList[i].PhaseList[j].SpawnList[k].SpawnDelay = 0;
                WaveList[i].PhaseList[j].SpawnList[k].SpawnHasSpawned = 0;
                WaveList[i].PhaseList[j].SpawnList[k].SpawnQuantity = 0;
            }
            WaveList[i].PhaseList[j].PhaseHasSpawned = 0;
            WaveList[i].PhaseList[j].PhaseSpawnListSize = 0;
            WaveList[i].PhaseList[j].PhaseTotalEnemy = 0;
        }
        WaveList[i].WaveCurrentPhase = 0;
        WaveList[i].WaveHasSpawned = 0;
        WaveList[i].WavePhaseListSize = 0;
        WaveList[i].WaveTotalEnemy = 0;
    }
    
    PhaseTimer = 2000000000;
}

void WaveManager::ReadConfig(MapType _MapType) {
    std::fstream ConfigFile(ResourceManager::GetInstance().GetResourcePath("game/Config_" + ResourceManager::ParseMapTypeToString[(int) _MapType] + ".txt"), std::ios::in);
    assert((ConfigFile.is_open()) && "WaveManager * Failed To Load Config File");

    std::string LineReadingBuffer;
    char EnemyTypeBuffer[128];
    bool IsWaveConfigFieldFound = false;

    while (!ConfigFile.eof()) {
        std::getline(ConfigFile, LineReadingBuffer);
        if (LineReadingBuffer == "Wave Config:") {
            IsWaveConfigFieldFound = true;
            break;
        }
    }

    assert(IsWaveConfigFieldFound && "WaveManager * Failed To Read Wave Config Field");

    std::getline(ConfigFile, LineReadingBuffer);

    sscanf(LineReadingBuffer.c_str(), "Wave Amount: %d", &WaveListSize);
    assert(WaveListSize <= MAX_WAVE && "WaveManager * Wave Amount Exceed Limit");
    assert(WaveListSize > 0 && "WaveManager * Invalid Wave Amount");

    ConfigFile.ignore();
    for (int i = 0; i < WaveListSize; i++) {

        std::getline(ConfigFile, LineReadingBuffer);
        sscanf(LineReadingBuffer.c_str(), "Phase Amount: %d", &WaveList[i].WavePhaseListSize);

        for (int j = 0; j < WaveList[i].WavePhaseListSize; j++) {

            std::getline(ConfigFile, LineReadingBuffer);
            sscanf(LineReadingBuffer.c_str(), "Spawn Amount: %d", &WaveList[i].PhaseList[j].PhaseSpawnListSize);

            for (int k = 0; k < WaveList[i].PhaseList[j].PhaseSpawnListSize; k++) {

                std::getline(ConfigFile, LineReadingBuffer);
                sscanf(LineReadingBuffer.c_str(), "Type: %[^ ] Quantity: %d Delay: %d", &EnemyTypeBuffer[0], &WaveList[i].PhaseList[j].SpawnList[k].SpawnQuantity, &WaveList[i].PhaseList[j].SpawnList[k].SpawnDelay);
                WaveList[i].PhaseList[j].SpawnList[k].SpawnEnemyType = ResourceManager::ParseStringToEnemyType.find(std::string(EnemyTypeBuffer))->second;
                
                WaveList[i].PhaseList[j].PhaseTotalEnemy += WaveList[i].PhaseList[j].SpawnList[k].SpawnQuantity;
            }
            WaveList[i].WaveTotalEnemy += WaveList[i].PhaseList[j].PhaseTotalEnemy;
        }
        ConfigFile.ignore();
    }
}


void WaveManager::Update() {
    size_t Timer = GameManager::GetTime();

    SpawnData* TempSpawnData;
    for (int i = 0; i < CurrentPhasePointer->PhaseSpawnListSize; i++) {
        TempSpawnData = &CurrentPhasePointer->SpawnList[i];
        if (TempSpawnData->SpawnHasSpawned < TempSpawnData->SpawnQuantity) {
            if (TempSpawnData->SpawnDelay == 0 || Timer % TempSpawnData->SpawnDelay == 0) {
                GameManager::AddEnemy(TempSpawnData->SpawnEnemyType);
                TempSpawnData->SpawnHasSpawned++;
                CurrentPhasePointer->PhaseHasSpawned++;
                CurrentWavePointer->WaveHasSpawned++;
            }
        }
    }


    if (GameManager::GetCurrentEnemyAmount() == 0) {
        if (CurrentPhasePointer->PhaseHasSpawned == CurrentPhasePointer->PhaseTotalEnemy) {
            if (CurrentWavePointer->WaveHasSpawned == CurrentWavePointer->WaveTotalEnemy) {
                if (WaveListSize == CurrentWaveIndex - 1) {
                    printf("xong");
                    assert("Chua Lam");
                } else {
                    CurrentWaveIndex++;
                    CurrentWavePointer = &WaveList[CurrentWaveIndex];
                    CurrentPhasePointer = &CurrentWavePointer->PhaseList[0];
                }
            } else {
                CurrentWavePointer->WaveCurrentPhase++;
                CurrentPhasePointer = &CurrentWavePointer->PhaseList[CurrentWavePointer->WaveCurrentPhase];
            }
            PhaseTimer = GameManager::GetInstance().GetTime();
        } 
    }
}