#pragma once

#include "Game/Enemy.h"

class WrathSlimeEnemy : public Enemy {
private:
	static constexpr unsigned int BASE_HEALTH = 150;
	static constexpr float BASE_SPEED = 75;
	static constexpr unsigned int BASE_CASH_DROP = 500;
	float SizeFactor;
	bool Used;
public:
	WrathSlimeEnemy();
	
	void Update();
	void Draw();
	void DrawHealthBar();
	void OnDamaged(const unsigned int&);
};