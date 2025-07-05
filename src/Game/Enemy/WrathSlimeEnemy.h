#pragma once

#include "Game/Enemy.h"

class WrathSlimeEnemy : public Enemy {
private:
	static constexpr size_t BASE_HEALTH = 150;
	static constexpr size_t BASE_SPEED = 75;
	static constexpr size_t BASE_CASH_DROP = 500;
	float SizeFactor;
	bool Used;
public:
	WrathSlimeEnemy();
	
	void Update();
	void Draw();
	void DrawHealthBar();
	void OnDamaged(const size_t&);
};