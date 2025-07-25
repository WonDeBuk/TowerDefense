#pragma once

#include "Game/Enemy.h"

class Brawler : public Enemy {
private:
	static constexpr float BASE_HEALTH = 11350.0f;
	static constexpr float BASE_SPEED = 1.25f;
	int MaxBounceCount;
	int CurrentBounceCount;
	Vector2 MemoryPosition;
protected:
	void UpdateAnimation() override;
	void FindLanding();
public:
	Brawler();

	void OnHeal(const float& _Heal) override;
	void OnDamage(const float& _Damage) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};