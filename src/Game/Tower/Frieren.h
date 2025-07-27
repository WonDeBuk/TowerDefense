#pragma once

#include "Game/Tower.h"

class Frieren: public Tower {
private:
	int MaxShotAvailable;
	int ShotRemaining;
	Color UpgradeColor; //delete later lmao
	void (Frieren::*OnCooldown)();

	void AttackModule_1();
	void AttackModule_3();
public:
	Frieren();

	void OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
	void Draw() const override;
};