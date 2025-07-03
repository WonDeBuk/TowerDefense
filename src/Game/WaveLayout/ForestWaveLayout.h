#pragma once

#include "Game/WaveLayout.h"

class ForestWaveLayout : public WaveLayout {
private:
	ForestWaveLayout();
public:
	~ForestWaveLayout();
	static ForestWaveLayout& GetInstance();
};