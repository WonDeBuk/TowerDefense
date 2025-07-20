#pragma once

#include "Game/Enemy.h"

class Golem : public Enemy {
private:
	static constexpr float BASE_HEALTH = 350.0f;
	static constexpr float BASE_SPEED = 1.75f;
protected:
	void UpdateAnimation() override;
	EnemyAnimationState CurrentAnimationState;

public:
	Golem();

	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};