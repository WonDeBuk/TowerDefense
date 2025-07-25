#pragma once

#include "Game/Enemy.h"

class Titan : public Enemy {
private:
	static constexpr float BASE_HEALTH = 125000.0f;
	static constexpr float BASE_SPEED = 0.95f;
	static constexpr float BASE_ABILITY_RANGE = 100.0f;
protected:
	void UpdateAnimation() override;
	void Nullify();
public:
	Titan();

	void OnHeal(const float& _Heal) override;
	void OnDeath() override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};