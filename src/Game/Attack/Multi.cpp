#include "Multi.h"
#include "Game/GameManager.h"
#include <iostream>

Multi::~Multi() {}
void Multi::Update() {}
void Multi::Draw() const {}

Multi::Multi() {
	StartOfList = 0;
	EndOfList = 0;
	ListSize = 0;
	CheckForValidHit = &Multi::CheckForPreserveHit;
}

void Multi::SetHitType(const HitType& _HitType) {
	if (_HitType == HitType::OVERRIDE) CheckForValidHit = &Multi::CheckForOverrideHit;
	else CheckForValidHit = &Multi::CheckForPreserveHit;
}

bool Multi::CheckForOverrideHit() {
	if (TotalHit <= 0) {
		OnDeath();
		Attack::AttackKill();
		return true;
	}
	int Counter = GameManager::GetInstance().GetCurrentEnemyAmount();
	if (Counter <= 0) return false;

	//update black list data
	while (ListSize > 0 && EnemyBlackList[StartOfList].TimeAdded - Lifespan >= BLACK_LIST_TIME) {
		StartOfList = (StartOfList + 1) % BLACK_LIST_SIZE;
		ListSize--;
	}

	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetEnemyPoolTracker();
	//iterate over every living enemy
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i] == true) {
			bool IsInList = false;
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (CheckCollisionPointRec(AttackCurrentPosition, Object->GetHitBox())) {
				//check if the enemy is inside the list
				for (int k = 0; k < ListSize; k++) {
					//enemy found
					if (EnemyBlackList[(StartOfList + k) % BLACK_LIST_SIZE].EnemyID == i) {
						IsInList = true;
						break;
					}
				}

				//if it is not in the list, append it
				if (!IsInList) {
					//if the list is full
					if (ListSize >= BLACK_LIST_SIZE) {
						//if the first element and the considered one is less than 6 frames apart, stop the operation as every enemy after will also be like this
						if (EnemyBlackList[EndOfList].TimeAdded < Lifespan + 6) return false;
						StartOfList = (StartOfList + 1) % BLACK_LIST_SIZE;
						ListSize--;
					}
					//decrease the total hit as this is a successful hit
					TotalHit--;
					Object->OnDamage(AttackDamage);
					EnemyBlackList[EndOfList].EnemyID = i;
					EnemyBlackList[EndOfList].TimeAdded = Lifespan;
					EndOfList = (EndOfList + 1) % BLACK_LIST_SIZE;
					ListSize++;

					//if TotalHit reaches 0, the attack expires, thus returning true
					if (TotalHit == 0) {
						OnDeath();
						Attack::AttackKill();
						return true;
					}
				}
			}
			//check for an early exit
			Counter--;
			if (Counter == 0) return false;
		}
	}
	return false;
}

bool Multi::CheckForPreserveHit() {
	if (TotalHit <= 0) {
		OnDeath();
		Attack::AttackKill();
		return true;
	}
	int Counter = GameManager::GetInstance().GetCurrentEnemyAmount();
	if (Counter <= 0) return false;
	
	while (ListSize > 0 && EnemyBlackList[StartOfList].TimeAdded - Lifespan >= BLACK_LIST_TIME) {
		StartOfList = (StartOfList + 1) % BLACK_LIST_SIZE;
		ListSize--;
	}
	
	if (ListSize >= BLACK_LIST_SIZE) return false;

	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetEnemyPoolTracker();
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i] == true) {
			bool IsInList = false;
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (CheckCollisionPointRec(AttackCurrentPosition, Object->GetHitBox())) {
				for (int k = 0; k < ListSize; k++) {
					if (EnemyBlackList[(StartOfList + k) % BLACK_LIST_SIZE].EnemyID == i) {
						IsInList = true;
						break;
					}
				}
			}

			if (!IsInList) {
				TotalHit--;
				Object->OnDamage(AttackDamage);
				EnemyBlackList[EndOfList].EnemyID = i;
				EnemyBlackList[EndOfList].TimeAdded = Lifespan;
				EndOfList = (EndOfList + 1) % BLACK_LIST_SIZE;
				ListSize++;

				if (TotalHit == 0) {
					OnDeath();
					Attack::AttackKill();
					return true;
				}

				if (ListSize >= BLACK_LIST_SIZE) return false;
			}

			Counter--;
			if (Counter == 0) return false;
		}
	}
	return false;
}