#pragma once

#include "Game/Tower.h"

class Shuna : public Tower {
private:
	bool IsWindUp;
	int TargetEnemyID[15];
	int CurrentTargetCount;
	int MaxTarget;
	void (Shuna::* OnCooldown)();

	void AttackModule();
public:
	Shuna();

	void GetFirstEnemy() override;
	void GetLastEnemy() override;
	void GetWeakestEnemy() override;
	void GetStrongestEnemy() override;

	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
};
