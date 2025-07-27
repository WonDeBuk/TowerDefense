#pragma once

#include "Game/Enemy.h"

class Dragon : public Enemy {
private:
	static constexpr float BASE_HEALTH = 35000.0f;
	static constexpr float BASE_SPEED = 0.5f;
protected:
	void UpdateAnimation() override;
public:
	Dragon();

	void OnHeal(const float& _Heal) override;
	void OnDamage(const float& _Damage) override;

	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};