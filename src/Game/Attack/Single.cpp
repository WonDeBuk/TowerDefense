#include "Single.h"
#include "Game/GameManager.h"
#include <iostream>

Single::~Single() {}
void Single::Update() {}
void Single::Draw() const {}

Single::Single() {
	CheckForValidHit = &Single::CheckForAimlessHit;
}

void Single::SetHitType(const HitType& _HitType) {
	if (_HitType == HitType::TARGETED) CheckForValidHit = &Single::CheckForTargetedHit;
	else CheckForValidHit = &Single::CheckForAimlessHit;
}

bool Single::CheckForTargetedHit() {
	if (GameManager::GetInstance().GetEnemyPoolTracker()[TargetID] == false) {
		CheckForValidHit = &Single::CheckForAimlessHit;
		return false;
	}

	Enemy* Object = GameManager::GetInstance().GetEnemyByID(TargetID);
	if (CheckCollisionPointRec(AttackCurrentPosition, Object->GetHitBox())) {
		Object->OnDamage(AttackDamage);
		OnDeath();
		Attack::AttackKill();
		return true;
	}
	return false;
}

bool Single::CheckForAimlessHit() {
	int Counter = GameManager::GetInstance().GetCurrentEnemyAmount();
	if (Counter <= 0) return false;
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetEnemyPoolTracker();
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i] == true) {
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (CheckCollisionPointRec(AttackCurrentPosition, Object->GetHitBox())) {
				Object->OnDamage(AttackDamage);
				OnDeath();
				Attack::AttackKill();
				return true;
			}
			
			Counter--;
			if (Counter == 0) return false;
		}
	}
	return false;
}