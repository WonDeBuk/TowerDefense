#pragma once

#include "GameManager.h"
#include "WaveLayout.h"

class WaveManager {
private:
	Rectangle SkipButton;
	unsigned short CurrentWave;
	unsigned short CurrentEnemy;
	bool IntermissionTime;
	size_t WaveTime;
	WaveLayout* CurrentLayout;

	WaveManager() {
		SkipButton = { 10, 300, 100, 40 };
		CurrentWave = 0;
		CurrentEnemy = 0;
		IntermissionTime = true;
		WaveTime = 0;
		CurrentLayout = nullptr;
	}

public:
	static WaveManager& GetInstance();
	void SwitchTo(const WaveLayoutType&);
	bool Invoke();
	void Update();
	void Draw();
};

