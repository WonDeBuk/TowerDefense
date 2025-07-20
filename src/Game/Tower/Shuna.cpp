#include "Shuna.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include <raymath.h>
#include <iostream>

Shuna::Shuna(): Tower() {
	CurrentChampion = ChampionType::SHUNA;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 25;
	TowerCooldown = 150;
	TotalCost = 500;
	TowerRange = 300.0f;
	TowerAttackDamage = 15.0f;
	TowerAttackMovementSpeed = 9.0f;
	CurrentTargetCount = 0;
	MaxTarget = 2;

	IsWindUp = false;
	OnCooldown = &Shuna::AttackModule;
}

void Shuna::GetFirstEnemy() {
	CurrentTargetCount = 0;
	GameManager& gm = GameManager::GetInstance();
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = gm.GetEnemyByID(i);
			if (Vector2Distance(TowerPosition, Object->GetEnemyCurrentPosition()) < TowerRange) {
				int ConsideredWaypointIndex = Object->GetHeaddingWaypointIndex();
				float ConsideredDistance = Vector2Distance(gm.GetWaypointByIndex(ConsideredWaypointIndex), Object->GetEnemyCurrentPosition());

				int find = CurrentTargetCount - 1;
				while (find >= 0) {
					Enemy* ThresholdObject = gm.GetEnemyByID(TargetEnemyID[find]);
					int ThresholdWaypointIndex = ThresholdObject->GetHeaddingWaypointIndex();

					bool IsCloserToBase = (ConsideredWaypointIndex > ThresholdWaypointIndex);
					if (ConsideredWaypointIndex == ThresholdWaypointIndex) {
						float ThresholdDistance = Vector2Distance(gm.GetWaypointByIndex(ThresholdWaypointIndex), ThresholdObject->GetEnemyCurrentPosition());
						IsCloserToBase = (ConsideredDistance < ThresholdDistance);
					}

					if (IsCloserToBase) {
						if (find + 1 < MaxTarget) TargetEnemyID[find + 1] = TargetEnemyID[find];
						find--;
					}
					else break;
				}
				if (find + 1 < MaxTarget) {
					TargetEnemyID[find + 1] = Object->GetEnemyID();
					if (CurrentTargetCount < MaxTarget) CurrentTargetCount++;
				}
			}
		}
	}
}

void Shuna::GetLastEnemy() {
	CurrentTargetCount = 0;
	GameManager& gm = GameManager::GetInstance();
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = gm.GetEnemyByID(i);
			if (Vector2Distance(TowerPosition, Object->GetEnemyCurrentPosition()) < TowerRange) {
				int ConsideredWaypointIndex = Object->GetHeaddingWaypointIndex();
				float ConsideredDistance = Vector2Distance(gm.GetWaypointByIndex(ConsideredWaypointIndex), Object->GetEnemyCurrentPosition());

				int find = CurrentTargetCount - 1;
				while (find >= 0) {
					Enemy* ThresholdObject = gm.GetEnemyByID(TargetEnemyID[find]);
					int ThresholdWaypointIndex = ThresholdObject->GetHeaddingWaypointIndex();

					bool IsCloserToBase = (ConsideredWaypointIndex < ThresholdWaypointIndex);
					if (ConsideredWaypointIndex == ThresholdWaypointIndex) {
						float ThresholdDistance = Vector2Distance(gm.GetWaypointByIndex(ThresholdWaypointIndex), ThresholdObject->GetEnemyCurrentPosition());
						IsCloserToBase = (ConsideredDistance > ThresholdDistance);
					}

					if (IsCloserToBase) {
						if (find + 1 < MaxTarget) TargetEnemyID[find + 1] = TargetEnemyID[find];
						find--;
					}
					else break;
				}
				if (find + 1 < MaxTarget) {
					TargetEnemyID[find + 1] = Object->GetEnemyID();
					if (CurrentTargetCount < MaxTarget) CurrentTargetCount++;
				}
			}
		}
	}
}

void Shuna::GetWeakestEnemy() {
	CurrentTargetCount = 0;
	GameManager& gm = GameManager::GetInstance();
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = gm.GetEnemyByID(i);
			if (Vector2Distance(TowerPosition, Object->GetEnemyCurrentPosition()) < TowerRange) {
				int find = CurrentTargetCount - 1;
				while (find >= 0 && Object->GetEnemyHealth() < gm.GetEnemyByID(TargetEnemyID[find])->GetEnemyHealth()) {
					if (find + 1 < MaxTarget) TargetEnemyID[find + 1] = TargetEnemyID[find];
					find--;
				}

				if (find + 1 < MaxTarget) {
					TargetEnemyID[find + 1] = Object->GetEnemyID();
					if (CurrentTargetCount < MaxTarget) CurrentTargetCount++;
				}
			}
		}
	}
}

void Shuna::GetStrongestEnemy() {
	CurrentTargetCount = 0;
	GameManager& gm = GameManager::GetInstance();
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = gm.GetEnemyByID(i);
			if (Vector2Distance(TowerPosition, Object->GetEnemyCurrentPosition()) < TowerRange) {
				int find = CurrentTargetCount - 1;
				while (find >= 0 && Object->GetEnemyHealth() > gm.GetEnemyByID(TargetEnemyID[find])->GetEnemyHealth()) {
					if (find + 1 < MaxTarget) TargetEnemyID[find + 1] = TargetEnemyID[find];
					find--;
				}

				if (find + 1 < MaxTarget) {
					TargetEnemyID[find + 1] = Object->GetEnemyID();
					if (CurrentTargetCount < MaxTarget) CurrentTargetCount++;
				}
			}
		}
	}
}

void Shuna::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x - 40.0f, TowerPosition.y - 96.0f };
}

void Shuna::AttackModule() {
	(this->*GetTargetEnemy)();
	if (CurrentTargetCount == 0) {
		if (IsWindUp) {
			IsWindUp = false;
			if (TowerLifespan - PreviousAttackFrame == 56) AttackPosition.x -= 80.0f;
		}
		return;
	}
	if (IsWindUp == false) {
		CurrentAnimationState = ChampionAnimationState::CAST;
		IsWindUp = true;
		return;
	}

	for (int i = 0; i < CurrentTargetCount; i++) {
		Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID[i]);
		size_t CalcLifespan = Vector2Distance(TowerPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed * 1.5f;
		GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID[i], TowerID, CalcLifespan, GREEN));
	}

	if (TowerLifespan - PreviousAttackFrame == 56) {
		IsWindUp = false;
		AttackPosition.x -= 80.f;
	}
	else AttackPosition.x += 80.0f;
}

bool Shuna::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerRange = 335.0f;
		TowerAttackDamage = 20.0f;
		TowerAttackMovementSpeed = 9.25f;
		MaxTarget = 3;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 135;
		TowerRange = 365.0f;
		TowerAttackDamage = 25.0f;
		TowerAttackMovementSpeed = 9.75f;
		MaxTarget = 5;
		TotalCost += 000;
		break;
	}
	return true;
}

void Shuna::Update() {
	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown && !IsWindUp) {
		(this->*OnCooldown)();
		if (IsWindUp) {
			PreviousAttackFrame = TowerLifespan;
		}
	}

	size_t DeltaFire = TowerLifespan - PreviousAttackFrame;
	if (IsWindUp && (DeltaFire == 21 || DeltaFire == 56)) {
		(this->*OnCooldown)();
	}

	if (TowerLifespan - PreviousAttackFrame == 70) {
		CurrentAnimationState = ChampionAnimationState::IDLE;
	}
	TowerLifespan++;
}

void Shuna::UpdateAnimation() {

}