#include "Tower.h"
#include "GameManager.h"
#include <iostream>
#include <raymath.h>

Tower::Tower() {
	TowerLevel = 1;
	TowerLifespan = 0;
	TargetEnemyID = -1;
}

void Tower::SetTargetType(const TargetType& _TargetType) {
	switch (_TargetType) {
	case LAST:
		GetTargetEnemy = &Tower::GetLastEnemy;
		break;
	case WEAKEST:
		GetTargetEnemy = &Tower::GetWeakestEnemy;
		break;
	case STRONGEST:
		GetTargetEnemy = &Tower::GetStrongestEnemy;
		break;
	case FIRST:
	default:
		GetTargetEnemy = &Tower::GetFirstEnemy;
	}
}

void Tower::SetTowerID(const int& _ID) {
	TowerID = _ID;
	TowerPosition = GameManager::GetInstance().GetTowerPlotByID(_ID);
	SetTargetType(FIRST);
}

void Tower::SetTowerRange(const float& _TowerRange) {
	TowerRange = _TowerRange;
}

void Tower::GetFirstEnemy() {
	const bool (&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetEnemyPoolTracker();
	Enemy* Target = nullptr;
	float CurrentDistance;
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (Vector2DistanceSqr(TowerPosition, Object->GetEnemyCurrentPosition()) <= TowerRange * TowerRange) {
				int TempHeaddingWaypointIndex = Object->GetHeaddingWaypointIndex();
				float TempDistance = Vector2DistanceSqr(GameManager::GetInstance().GetWaypointByIndex(TempHeaddingWaypointIndex), Object->GetEnemyCurrentPosition());

				if (Target == nullptr || TempHeaddingWaypointIndex > Target->GetHeaddingWaypointIndex() || (TempHeaddingWaypointIndex == Target->GetHeaddingWaypointIndex() && TempDistance < CurrentDistance)) {
					Target = Object;
					CurrentDistance = TempDistance;
				}
			}
		}
	}
	if (Target) TargetEnemyID = Target->GetEnemyID();
	else TargetEnemyID = -1;
}

void Tower::GetLastEnemy() {
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetEnemyPoolTracker();
	Enemy* Target = nullptr;
	float CurrentDistance;
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (Vector2DistanceSqr(TowerPosition, Object->GetEnemyCurrentPosition()) <= TowerRange * TowerRange) {
				int TempHeaddingWaypointIndex = Object->GetHeaddingWaypointIndex();
				float TempDistance = Vector2DistanceSqr(GameManager::GetInstance().GetWaypointByIndex(TempHeaddingWaypointIndex), Object->GetEnemyCurrentPosition());

				if (Target == nullptr || TempHeaddingWaypointIndex < Target->GetHeaddingWaypointIndex() || (TempHeaddingWaypointIndex == Target->GetHeaddingWaypointIndex() && TempDistance > CurrentDistance)) {
					Target = Object;
					CurrentDistance = TempDistance;
				}
			}
		}
	}
	if (Target) TargetEnemyID = Target->GetEnemyID();
	else TargetEnemyID = -1;
}

void Tower::GetWeakestEnemy() {
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetAttackPoolTracker();
	Enemy* Target = nullptr;
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (Vector2DistanceSqr(TowerPosition, Object->GetEnemyCurrentPosition()) <= TowerRange * TowerRange) {
				if (Target == nullptr || Object->GetEnemyHealth() < Target->GetEnemyHealth()) {
					Target = Object;
				}
			}
		}
	}

	if (Target) TargetEnemyID = Target->GetEnemyID();
	else TargetEnemyID = -1;
}

void Tower::GetStrongestEnemy() {
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetAttackPoolTracker();
	Enemy* Target = nullptr;
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (Vector2DistanceSqr(TowerPosition, Object->GetEnemyCurrentPosition()) <= TowerRange * TowerRange) {
				if (Target == nullptr || Object->GetEnemyHealth() > Target->GetEnemyHealth()) {
					Target = Object;
				}
			}
		}
	}

	if (Target) TargetEnemyID = Target->GetEnemyID();
	else TargetEnemyID = -1;
}

const Vector2 Tower::GetEnemyDefinitePosition(const Vector2& _AttackStartPosition) const {
	Enemy* Target = GameManager::GetInstance().GetEnemyByID(TargetEnemyID);
	Vector2 EnemyFuturePosition = Target->GetEnemyCurrentPosition();
	float Eta = Vector2Distance(_AttackStartPosition, EnemyFuturePosition) / TowerAttackMovementSpeed;
	for (int i = 0; i < 8; i++) {
		EnemyFuturePosition = Target->GetEnemyFuturePosition((int)Eta);
		float Eta2 = Vector2Distance(_AttackStartPosition, EnemyFuturePosition) / TowerAttackMovementSpeed;
		if (fabs(Eta - Eta2) < 0.0f) {
			break;
		}
		Eta = (Eta2 + Eta) * 0.5f;
	}
	return EnemyFuturePosition;
}