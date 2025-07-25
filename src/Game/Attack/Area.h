#pragma once

#include "Game/Attack.h"

class Area : public Attack {
private:
	//the explosion radius and distance needed to travel is store within AttackDestinationPosition;
	void OnExpire();
public:
	static const Attack* AreaTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _ExplosionRadius, const float& _AttackDamage, const float& _AttackMovementSpeed, const int& AttackOwnTowerID, const int& _Lifespan);

	void Update() override;
	void Draw() const override;
};