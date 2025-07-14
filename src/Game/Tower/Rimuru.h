#pragma once

#include "Game/Tower.h"

class Rimuru : public Tower {
private:
	Color UpgradeColor;
	void (Rimuru::* OnCooldown)();

	void AttackModule();
public:
	Rimuru();

	void OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
	void Draw() const override;
};