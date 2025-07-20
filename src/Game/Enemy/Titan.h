#pragma once

#include "Game/Enemy.h"

class Titan : public Enemy {
private:
	static constexpr float BASE_HEALTH = 100.0f;
	static constexpr float BASE_SPEED = 1.15f;
protected:
	void UpdateAnimation() override;
	EnemyAnimationState CurrentAnimationState;

public:
	Titan();

	void OnDeath() override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};