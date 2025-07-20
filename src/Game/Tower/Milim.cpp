#include "Milim.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include <raymath.h>

Milim::Milim(): Tower() {
	CurrentChampion = ChampionType::MILIM;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 140;
	TowerCooldown = 175;
	TotalCost = 700;
	TowerRange = 500.0f;
	TowerAttackDamage = 100.0f;
	TowerAttackMovementSpeed = 15.0f;
	TotalShot = 1;

	IsWindUp = false;
	OnCooldown = &Milim::AttackModule;
}

void Milim::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x, TowerPosition.y - 16.0f };
}

void Milim::AttackModule() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (IsWindUp) {
			IsWindUp = false;
		}
		return;
	}
	if (IsWindUp == false) {
		CurrentAnimationState = ChampionAnimationState::CAST;
		IsWindUp = true;
		return;
	}

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, GREEN));
	IsWindUp = false;
}

bool Milim::OnUpgrade() {
	if (TowerLevel == 3) return false;	
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerCooldown = 160;
		TowerRange = 575.0f;
		TowerAttackDamage = 150.0f;
		TowerAttackMovementSpeed = 15.0f;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 140;
		TowerRange = 675.0f;
		TowerAttackDamage = 250.0f;
		TowerAttackMovementSpeed = 20.0f;
		TotalCost += 000;
		break;
	}
	return true;
}

void Milim::Update() {
	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown && !IsWindUp) {
		(this->*OnCooldown)();
		if (IsWindUp) {
			PreviousAttackFrame = TowerLifespan;
		}
	}

	size_t DeltaFire = TowerLifespan - PreviousAttackFrame;
	if (IsWindUp && DeltaFire == 49) {
		(this->*OnCooldown)();
	}

	if (TowerLifespan - PreviousAttackFrame == 70) {
		CurrentAnimationState = ChampionAnimationState::IDLE;
	}

	TowerLifespan++;
}
