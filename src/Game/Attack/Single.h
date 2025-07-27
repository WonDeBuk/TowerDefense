#pragma once

#include "Game/Attack.h"

class Single : public Attack {
protected:
	int TargetID;	
	bool (Single::*CheckForValidHit)();
	
	virtual void SetHitType(const HitType& _HitType);
	virtual bool CheckForTargetedHit();
	virtual bool CheckForAimlessHit();
public:
	~Single();
	Single();

	void Update() override;
	void Draw() const override;
};