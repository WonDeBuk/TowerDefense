#pragma once

#include "Game/Enemy.h"

class Bandit : public Enemy {
private:
	static constexpr float BASE_HEALTH = 350.0f;
	static constexpr float BASE_SPEED = 3.0f;
	static constexpr int MAX_CASH_CAPACITY = 1000;
protected:
	int CashStolen;
	void UpdateAnimation() override;
public:
	Bandit();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};