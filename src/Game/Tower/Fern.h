#pragma once

#include "Game/Tower.h"

class Fern : public Tower {
private:
	void (Fern::* OnCooldown)();

	void AttackModule();
public:
	Fern();

	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
};
