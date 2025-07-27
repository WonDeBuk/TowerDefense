#pragma once

#include "Game/Enemy.h"

class Golem : public Enemy {
private:
	static constexpr float BASE_HEALTH = 1800.0f;
	static constexpr float BASE_SPEED = 1.35f;

	void FindDestination();
protected:
	void UpdateAnimation() override;
public:
	Golem();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};