#pragma once

#include "Game/Enemy.h"

class SniperSlimeEnemy : public Enemy {
	static constexpr size_t BASE_HEALTH = 150;
	static constexpr size_t BASE_SPEED = 25;
	static constexpr size_t BASE_CASH_DROP = 75;
public:
	SniperSlimeEnemy();

	void Draw();
	void DrawHealthBar();
	void Update();
};