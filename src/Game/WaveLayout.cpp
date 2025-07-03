#include "WaveLayout.h"
#include "WaveLayout/ForestWaveLayout.h"

EnemyType ConvertToEnemyType(const std::string& _s) {
	if (_s == "ENEMY_SLIME") return ENEMY_SLIME;
	return ENEMY_NONE;
}

WaveLayout& WaveLayout::GetInstance(const WaveLayoutType& _type) {
	switch (_type) {
	case WAVE_LAYOUT_FOREST:
		return ForestWaveLayout::GetInstance();
	}
}

WaveLayout::WaveLayout() {
	for (unsigned short i = 0; i < MaxWave; i++) {
		delete[] Layout[i];
	}
	delete[] Layout;
	delete[] MaxEnemyInWave;
}

WaveLayout::~WaveLayout() {

}

const unsigned short& WaveLayout::GetMaxWave() const {
	return MaxWave;
}

const unsigned short& WaveLayout::GetMaxEnemyInWave(const size_t& _wave) const {
	return MaxEnemyInWave[_wave];
}

TimedSpawn** WaveLayout::GetLayout() {
	return Layout;
}

TimedSpawn* WaveLayout::GetIndexLayout(const unsigned short& _index) {
	return Layout[_index];
}