#pragma once

#include "Game/Tower.h"

class Stark : public Tower {
private:
	 
	void (Stark::* OnCooldown)();

	void AttackModule();
public:
	Stark();

	bool OnUpgrade() override;
	void Update() override;
	void UpdateAnimation() override;
};
