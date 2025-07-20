#pragma once

#include "Game/Enemy.h"

class Grumble : public Enemy {
private:
	static constexpr float BASE_HEALTH = 1275.0f;
	static constexpr float BASE_SPEED = 0.75f;
protected:
	void UpdateAnimation() override;
	EnemyAnimationState CurrentAnimationState;

public:
	Grumble();

	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};