#pragma once

#include "../Attack.h"

class Ricochet : public Attack {
private:
	static constexpr int LIST_SIZE = 3;
	static Ricochet RicochetTemplate;
	int StartOfList;
	int EndOfList;
	int ListSize;
	int TotalPierce;
	Vector2 AttackRicochetDirection;
	BlackListData BlackList[LIST_SIZE];
public:
	static const Attack* RicochetTemplateBuildAndGet(const Vector2& _AttackStartPositon, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackOwnTowerID, const int& _Lifespan, const int& _TotalPierce, int _Exclusion = -1);
	void Draw() const override;
	void Update() override;
};