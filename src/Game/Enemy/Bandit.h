#pragma once

#include "Game/Enemy.h"

class Bandit : public Enemy {
private:
	static constexpr float BASE_HEALTH = 350.0f;
	static constexpr float BASE_SPEED = 2.25f;
protected:
	void UpdateAnimation() override;
	EnemyAnimationState CurrentAnimationState;

public:
	Bandit();

	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};