#pragma once

#include "Game/Tower.h"
#include <iostream>

class Stark : public Tower {
private:
	bool IsWindUp;
	int OutputAttackCount;
	Vector2 Test;
	void (Stark::* OnCooldown)();

	void AttackModule();
public:
	Stark();

	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
};
