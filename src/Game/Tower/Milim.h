#pragma once

#include "Game/Tower.h"

class Milim : public Tower {
private:
	bool IsWindUp;
	int TotalShot;
	void (Milim::*OnCooldown)();

	void AttackModule();
public:
	Milim();

	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() {}
};
