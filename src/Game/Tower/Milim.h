#pragma once

#include "Game/Tower.h"

class Milim : public Tower {
private:
	Color UpgradeColor;
	void (Milim::*OnCooldown)();

	void AttackModule();
public:
	Milim();

	void OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
	void Draw() const override;
};
