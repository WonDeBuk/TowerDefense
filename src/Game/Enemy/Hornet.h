#pragma once

#include "Game/Enemy.h"

class Hornet : public Enemy {
private:
	static constexpr float BASE_HEALTH = 350.0f;
	static constexpr float BASE_SPEED = 1.75f;
protected:
	void UpdateAnimation() override;
public:
	static const Enemy* HornetTemplateBuildAndGet(const Vector2& _EnemyCurrentPosition, const Vector2& _EnemyDirection, const int& _HeadingWaypointIndex);
	Hornet();

	void OnHeal(const float& _Heal) override;
	void OnDeath() override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};