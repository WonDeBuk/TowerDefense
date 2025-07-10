#pragma once

#include "./Utils/Define.h"
#include "GameManager.h"

class WaveManager {
private:
    static WaveData WaveList[MAX_WAVE];
    static int CurrentWaveIndex;
    static int WaveListSize;
    static WaveData* CurrentWavePointer;
    static PhaseData* CurrentPhasePointer;
public:
    static void ResetConfig();
    static void ReadConfig(MapType _MapType);
    static void Update();
};