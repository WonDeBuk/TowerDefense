#pragma once

#include "Game/Enemy.h"

class Brawler : public Enemy {
private:
	static constexpr float BASE_HEALTH = 350.0f;
	static constexpr float BASE_SPEED = 2.05f;
	float AnimationIndicator;
protected:
	void UpdateAnimation() override;
	EnemyAnimationState CurrentAnimationState;

public:
	Brawler();

	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};