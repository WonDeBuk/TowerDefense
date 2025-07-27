#pragma once

#include "Game/Tower.h"

class Shuna : public Tower {
private:
	int CurrentTargetCount;
	int MaxTarget;
	int TargetEnemyID[5];
	void (Shuna::* OnCooldown)();
	void AttackModule();
public:
	Shuna();

	void GetFirstEnemy() override;
	void GetLastEnemy() override;
	void GetWeakestEnemy() override;
	void GetStrongestEnemy() override;

	//void SetTargetType(const TargetType& _TargetType) override;
	void SetTowerID(const int& _TowerID) override;

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
};
