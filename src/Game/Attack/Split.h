#pragma once

#include "Game/Attack.h"

class Split : public Attack {
private:
	float InheritedDamage;
	int InheritLifespan;
	int NumberOfSplit;
	void OnExpire();
public:
	static const Attack* SplitTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackDamage, const float& _AttackMovementSpeed, const int& _NumberOfSplit, const float& _InheritDamage, const int& _InheritLifespan, const int& _AttackTargetID, const int& _AttackTowerOwnID, const int& _Lifespan);
	void Update() override;
	void Draw() const override;
};