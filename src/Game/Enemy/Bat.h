#pragma once

#include "Game/Enemy.h"

class Bat : public Enemy {
private:
	static constexpr float BASE_HEALTH = 170.0f;
	static constexpr float BASE_SPEED = 3.0f;
protected:
	void UpdateAnimation() override;
public:
	static const Enemy* BatTemplateBuildAndGet(const Vector2& _EnemyCurrentPosition, const Vector2& _EnemyDirection, const int& _HeadingWaypointIndex);
	Bat();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};