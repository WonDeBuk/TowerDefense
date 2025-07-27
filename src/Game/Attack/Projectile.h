#pragma once

#include "Game/Attack/Single.h"

class Projectile: public Single {
private:
public:
	static const Attack* ProjectileTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPositon, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _TargetEnemyID, const int& _OwnerID, const int& _Lifespan, const HitType& _HitType, const TextureData& _DeathTexture = Attack::NullTexture);
	void Draw() const override;
	void Update() override;
};