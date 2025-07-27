#include "Tower.h"
#include "GameManager.h"
#include "Utils/ResourceManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual/TowerBindVisual.h"

#include <iostream>
#include <raymath.h>

Tower::Tower() {
	StunTimer = 0;
	TowerLevel = 1;
	TowerLifespan = 0;
	PreviousAttackFrame = 0;
	TargetEnemyID = -1;
	IsWindUp = false;
	OutputAttackCount = 1;
	SetTargetType(TargetType::FIRST);
}

void Tower::SetTargetType(const TargetType& _TargetType) {
	switch (_TargetType) {
	case TargetType::LAST:
		GetTargetEnemy = &Tower::GetLastEnemy;
		break;
	case TargetType::WEAKEST:
		GetTargetEnemy = &Tower::GetWeakestEnemy;
		break;
	case TargetType::STRONGEST:
		GetTargetEnemy = &Tower::GetStrongestEnemy;
		break;
	case TargetType::FIRST:
	default:
		GetTargetEnemy = &Tower::GetFirstEnemy;
	}
}

void Tower::SetTowerID(const int& _ID) {
	TowerID = _ID;
	TowerPosition = GameManager::GetInstance().GetTowerPlotByID(_ID);
	SetTargetType(TargetType::FIRST);
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
			if (Vector2DistanceSqr(TowerPosition, GetEnemyDefinitePosition(TowerPosition, i)) <= TowerRange * TowerRange) {
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
			if (Vector2DistanceSqr(TowerPosition, GetEnemyDefinitePosition(TowerPosition, i)) <= TowerRange * TowerRange) {
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
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetEnemyPoolTracker();
	Enemy* Target = nullptr;
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (Vector2DistanceSqr(TowerPosition, GetEnemyDefinitePosition(TowerPosition, i)) <= TowerRange * TowerRange) {
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
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = GameManager::GetInstance().GetEnemyPoolTracker();
	Enemy* Target = nullptr;
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = GameManager::GetInstance().GetEnemyByID(i);
			if (Vector2DistanceSqr(TowerPosition, GetEnemyDefinitePosition(TowerPosition, i)) <= TowerRange * TowerRange) {
				if (Target == nullptr || Object->GetEnemyHealth() > Target->GetEnemyHealth()) {
					Target = Object;
				}
			}
		}
	}

	if (Target) TargetEnemyID = Target->GetEnemyID();
	else TargetEnemyID = -1;
}

const Vector2 Tower::GetEnemyDefinitePosition(const Vector2& _AttackStartPosition, const int& _TargetEnemyID) const {
	Enemy* Target = GameManager::GetInstance().GetEnemyByID(_TargetEnemyID);
	Vector2 EnemyFuturePosition = Target->GetEnemyCurrentPosition();
	float Eta = Vector2Distance(_AttackStartPosition, EnemyFuturePosition) / abs(TowerAttackMovementSpeed);
	for (int i = 0; i < 8; i++) {
		EnemyFuturePosition = Target->GetEnemyFuturePosition((int)Eta);
		float Eta2 = Vector2Distance(_AttackStartPosition, EnemyFuturePosition) / abs(TowerAttackMovementSpeed);
		if (fabs(Eta - Eta2) < 0.0f) {
			break;
		}
		Eta = (Eta2 + Eta) * 0.5f;
	}
	return EnemyFuturePosition;
}

void Tower::ApplyStun(const int& _StunTime) {
	if (_StunTime % 70 == 0) StunTimer += 7 - (_StunTime % 7);
	StunTimer += _StunTime;
}

bool Tower::OnUpgrade() {
	VisualManager::GetInstance().AddVisual(VisualType::TOWER_BIND, TowerBindVisual::TowerBindVisualTemplateBuildAndGet("ui/Upgrade.png", 15, { 39.0f, 112.0f }, { 78.0f, 135.0f }, TowerID, 3));
	return true;
}

void Tower::Draw() const {
	DrawCircleLines(TowerPosition.x, TowerPosition.y, TowerRange, RED);
	if (CurrentAnimationState == ChampionAnimationState::IDLE)
		ResourceManager::ChampionDataList[(int)CurrentChampion].ChampionDraw(CurrentAnimationState, TowerPosition, false, TowerLifespan);
	else ResourceManager::ChampionDataList[(int)CurrentChampion].ChampionDraw(CurrentAnimationState, TowerPosition, false, TowerLifespan % PreviousAttackFrame);
}