#pragma once

#include "Game/Tower.h"

class Frieren: public Tower {
private:
	int TowerDeltaCooldown;
	int MaxShotAvailable;
	int ShotRemaining;
	void (Frieren::*OnCooldown)();

	void AttackModule_1();
	void AttackModule_3();
public:
	Frieren();

	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() {}
	//void Draw() const override;
};