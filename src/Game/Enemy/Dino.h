#pragma once

#include "Game/Enemy.h"

class Dino : public Enemy {
private:
	static constexpr float BASE_HEALTH = 1450.0f;
	static constexpr float BASE_SPEED = 0.65f;
protected:
	void UpdateAnimation() override;
public:
	Dino();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};