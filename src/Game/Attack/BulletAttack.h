#pragma once
#include "../Attack.h"

class BulletAttack : public Attack {
private:
	static constexpr size_t BASE_DAMAGE = 25;
	static constexpr size_t BASE_SPEED = 2500;
	static constexpr size_t BASE_LIFESPAN = 5;
public:
	BulletAttack();
	~BulletAttack() override;

	void SetOrigin(const Vector2&) override;
	void SetDestination(const Vector2&) override;
	void Update() override;
	void Draw() override;
	void OnExpired() override;
	void Die() override;
};