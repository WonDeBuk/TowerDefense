#pragma once

#include "Game/Tower.h"

class Frieren: public Tower {
private:
	static constexpr int MIN_COOLDOWN = 10;
	int TowerDeltaCooldown;
	void (Frieren::*OnCooldown)();

	void AttackModule_1();
	void AttackModule_2();
public:
	Frieren();

	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() {}
	//void Draw() const override;
};