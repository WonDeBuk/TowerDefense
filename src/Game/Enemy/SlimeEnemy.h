#pragma once

#include "Game/Enemy.h"

class GameManager;

class SlimeEnemy : public Enemy {
private:
	static constexpr unsigned int BASE_HEALTH = 100;
	static constexpr float BASE_SPEED = 75;
	static constexpr unsigned int BASE_CASH_DROP = 25;
public:
	SlimeEnemy();
	
	void Update();
	void Draw();
	void DrawHealthBar();
};