#pragma once

#include "Game/Attack/Single.h"

class Area : public Single {
private:
	float ExplosionRadius;
public:
	static const Attack* AreaTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _ExplosionRadius, const float& _AttackDamage, const float& _AttackMovementSpeed, const int& AttackOwnTowerID, const int& _Lifespan, const HitType& _HitType, const TextureData& _DeathTexture);

	void OnDeath();
	void Update() override;
	void Draw() const override;
};