#pragma once

#include "Game/Attack/Multi.h"
#include <iostream>

class Ricochet : public Multi {
private:
public:
	static const Attack* RicochetTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPositon, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackOwnTowerID, const int& _Lifespan, const int& _TotalPierce, const HitType& _HitType, const int& _Exclusion = -1, const TextureData& _DeathTexture = Attack::NullTexture);
	
	void Draw() const override;
	void Update() override;
};