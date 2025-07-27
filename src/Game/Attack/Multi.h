#pragma once

#include "Game/Attack.h"

class Multi : public Attack {
protected:
	int StartOfList;
	int EndOfList;
	int ListSize;
	int TotalHit;
	BlackListData EnemyBlackList[BLACK_LIST_SIZE];
	bool (Multi::*CheckForValidHit)();

	virtual void SetHitType(const HitType& _HitType);
	virtual bool CheckForOverrideHit();
	virtual bool CheckForPreserveHit();
public:
	Multi();
	~Multi();

	void Update() override;
	void Draw() const override;
};