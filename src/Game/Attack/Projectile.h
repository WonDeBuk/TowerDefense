#pragma once

#include "../Attack.h"

class Projectile: public Attack {
private:
	static Projectile ProjectileTemplate;

	Vector2 AttackProjectileDirection;
public:
	static const Attack* ProjectileTemplateBuildAndGet(const Vector2& _AttackStartPositon, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackTargetID, const int& _AttackOwnTowerID);
	void Draw() const override;
	void Update() override;
};