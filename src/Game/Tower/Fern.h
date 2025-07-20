#pragma once

#include "Game/Tower.h"

class Fern : public Tower {
private:
	Color UpgradeColor;
	void (Fern::* OnCooldown)();

	void AttackModule();
public:
	Fern();

	void OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
	void Draw() const override;
};
