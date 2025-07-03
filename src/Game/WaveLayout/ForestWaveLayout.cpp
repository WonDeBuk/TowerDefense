#include "ForestWaveLayout.h"

ForestWaveLayout::ForestWaveLayout() {
	std::ifstream fin((std::string)ASSETS_PATH + "/structures/ForestWave.txt");
	if (!fin.is_open()) {
		std::cout << "[FOREST STRUCTURE]: Map data loaded " << (fin.is_open() ? "successfully!\n" : "failed...\n");
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

ForestWaveLayout::~ForestWaveLayout() {
	for (unsigned short i = 0; i < MaxWave; i++) {
		delete[] Layout[i];
	}
	delete[] Layout;
	delete[] MaxEnemyInWave;
}

ForestWaveLayout& ForestWaveLayout::GetInstance() {
	static ForestWaveLayout Instance;
	return Instance;
}