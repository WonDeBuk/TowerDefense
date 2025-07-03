#pragma once
#include <raylib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "Enemy.h"
#include "Utils/AssetManager.h"

struct TimedSpawn {
	EnemyType Type;
	size_t Time;
};

enum WaveLayoutType {
	WAVE_LAYOUT_FOREST
};

EnemyType ConvertToEnemyType(const std::string& _s);

class WaveLayout {
protected:
	WaveLayout();
	unsigned short* MaxEnemyInWave; //number of enemies per wave
	unsigned short MaxWave; //number of waves the game has
	size_t WaveTime; //the timer for the current wave
	TimedSpawn** Layout; //the list of enemies for the game
public:
	virtual ~WaveLayout();
	static WaveLayout& GetInstance(const WaveLayoutType&);
	virtual const unsigned short& GetMaxWave() const;
	virtual const unsigned short& GetMaxEnemyInWave(const size_t&) const;
	virtual TimedSpawn** GetLayout();
	virtual TimedSpawn* GetIndexLayout(const unsigned short&);
};