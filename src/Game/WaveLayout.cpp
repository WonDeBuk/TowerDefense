#include "WaveLayout.h"

EnemyType ConvertToEnemyType(const std::string& _s) {
	if (_s == "ENEMY_SLIME") return ENEMY_SLIME;
	if (_s == "ENEMY_WRATH_SLIME") return ENEMY_WRATH_SLIME;
	return ENEMY_NONE;
}

void WaveLayout::LoadContent(const WaveLayoutType& _type) {
	if (Layout != nullptr) return;

	std::string s = ASSETS_PATH + (std::string)"/structures/";
	switch (_type) {
	case WAVE_LAYOUT_FOREST:
		s += "ForestWave.txt";
		break;
	default:
		s += "ForestWave.txt";
	}

	std::ifstream fin(s);
	if (!fin.is_open()) {
		std::cout << "[STRUCTURE]: Map data loaded " << (fin.is_open() ? "successfully!\n" : "failed...\n");
		return;
	}
	std::string filler;
	getline(fin, filler);
	MaxWave = stoi(filler);
	Layout = new TimedSpawn * [MaxWave];
	MaxEnemyInWave = new unsigned short[MaxWave];
	size_t index = 0;
	while (getline(fin, filler)) {
		MaxEnemyInWave[index] = stoi(filler);
		Layout[index] = new TimedSpawn[MaxEnemyInWave[index]];
		size_t enemy = 0;
		while (getline(fin, filler) && !filler.empty()) {
			std::string	temp;
			std::stringstream str(filler);
			str >> temp;
			EnemyType TempType = ConvertToEnemyType(temp);
			str >> temp;
			size_t TempSpawnTime = stoi(temp);
			str >> temp;
			size_t TempQuantity = stoi(temp);
			if (enemy + TempQuantity >= MaxEnemyInWave[index]) TempQuantity = MaxEnemyInWave[index] - enemy;
			str >> temp;
			size_t TempDelay = stoi(temp);

			for (size_t j = 0; j < TempQuantity; j++) {
				Layout[index][enemy] = { TempType, TempSpawnTime + j * TempDelay };
				enemy++;
			}
		}
		index++;
	}
	fin.close();

}

WaveLayout::WaveLayout() {
	Layout = nullptr;
	MaxEnemyInWave = nullptr;
	WaveTime = 0;
	MaxWave = 0;
}

WaveLayout::~WaveLayout() {
	if (Layout == nullptr) return;
	for (unsigned short i = 0; i < MaxWave; i++) {
		delete[] Layout[i];
	}
	delete[] Layout;
	delete[] MaxEnemyInWave;
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