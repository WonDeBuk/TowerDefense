#pragma once

#include "Game/Enemy.h"

class GameManager;

class SlimeEnemy : public Enemy {
private:
	static constexpr size_t BASE_HEALTH = 100;
	static constexpr size_t BASE_SPEED = 75;
	static constexpr size_t BASE_CASH_DROP = 25;
public:
	SlimeEnemy();
	
	void Update();
	void Draw();
	void DrawHealthBar();
};