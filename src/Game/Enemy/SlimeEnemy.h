#pragma once

#include "Game/Enemy.h"

class GameManager;

class SlimeEnemy : public Enemy
{
private:
	friend class GameManager;
	static constexpr size_t BASE_HEALTH = 100;
	static constexpr size_t BASE_SPEED = 500;
	static constexpr size_t BASE_CASH_DROP = 25;
public:
	SlimeEnemy();
	~SlimeEnemy() override;

	void SetPosition(const Vector2&) override;
	void Update() override;
	void Draw() override;
	void OnDamaged(const size_t&) override;
	void OnDeath() override;
	void Die() override;
};