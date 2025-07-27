#pragma once

#include "Game/Tower.h"

class Fern : public Tower {
private:
	int SubAttackTotalHit;
	float SubAttackDamage;
	float SubAttackMovementSpeed;

	void (Fern::* OnCooldown)();

	void AttackModule_1();
	void AttackModule_2();
public:
	Fern();

	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
};
