#pragma once

#include "Game/Enemy.h"

class SniperSlimeEnemy : public Enemy {
	static constexpr unsigned int BASE_HEALTH = 150;
	static constexpr float BASE_SPEED = 25;
	static constexpr unsigned int BASE_CASH_DROP = 75;
public:
	SniperSlimeEnemy();

	void Draw();
	void DrawHealthBar();
	void Update();
};