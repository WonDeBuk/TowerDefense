#pragma once

#include "Game/Enemy.h"

class Healbot : public Enemy {
private:
	static constexpr float BASE_HEALTH = 350.0f;
	static constexpr float BASE_SPEED = 0.85f;
	static constexpr float BASE_HEAL = 1000.0f;
	static constexpr float BASE_HEAL_RANGE = 400.0f;
protected:
	void UpdateAnimation() override;
	void HealTarget();
public:
	Healbot();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};