#pragma once

#include "Game/Enemy.h"

class Revenant : public Enemy {
private:
	static constexpr float BASE_HEALTH = 12500.0f;
	static constexpr float BASE_SPEED = 0.85f;
protected:
	void UpdateAnimation() override;
	EnemyAnimationState CurrentAnimationState;

public:
	Revenant();

	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};