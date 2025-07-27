#pragma once

#include "Game/Tower.h"

class Stark : public Tower {
private:
	Color UpgradeColor;
	void (Stark::* OnCooldown)();

	void AttackModule();
public:
	Stark();

	void OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
	void Draw() const override;
};
