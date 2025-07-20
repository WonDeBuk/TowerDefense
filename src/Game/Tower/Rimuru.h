#pragma once

#include "Game/Tower.h"

class Rimuru : public Tower {
private:
	void (Rimuru::* OnCooldown)();

	void AttackModule();
public:
	Rimuru();

	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
};