#pragma once

#include "Game/Tower.h"

class Shuna : public Tower {
private:
	Color UpgradeColor;
	void (Shuna::* OnCooldown)();

	void AttackModule();
public:
	Shuna();

	void OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
	void Draw() const override;
};
