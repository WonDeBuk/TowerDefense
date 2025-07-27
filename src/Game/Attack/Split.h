#pragma once

#include "Game/Attack/Single.h"

class Split : public Single {
private:
	int SplitNumber;
	int SubAttackTotalHit;
	float SubAttackDamage;
	float SubAttackMovementSpeed;
	float SubAttackLifespan;
	TextureData SubAttackTexture;

public:
	static const Attack* SplitTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackDamage, const float& _AttackMovementSpeed, const int& _SplitNumber, const float& _SubAttackDamage, const float& _SubAttackMovementSpeed, const int& _SubAttackTotalHit, const int& _AttackTargetID, const int& _OwnerID, const int& _Lifespan, const int& _SubAttackLifespan, const HitType& _HitType, const TextureData& _SubAttackTexture, const TextureData& _DeathTexture = Attack::NullTexture);
	void OnCollide();
	void Update() override;
	void Draw() const override;
};