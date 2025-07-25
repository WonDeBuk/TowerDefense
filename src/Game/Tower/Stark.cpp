#include "Stark.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual/TowerBindVisual.h"
#include <raymath.h>

Stark::Stark() : Tower() {
	CurrentChampion = ChampionType::STARK;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 50;
	TowerCooldown = 120;
	TotalCost = 500;
	TowerRange = 300.0f;
	TowerAttackDamage = 75.0f;
	TowerAttackMovementSpeed = 7.0f;
	OutputAttackCount = 0;
	Test = { 0, 0 };
	OnCooldown = &Stark::AttackModule;
}

void Stark::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x, TowerPosition.y + 48.0f };
	SetTargetType(TargetType::STRONGEST);
}

void Stark::AttackModule() {
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
	Test = EnemyDefinitePosition;
	int CalcLifespan = Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed + 5;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, RED));
	Vector2 Parallel = Vector2Normalize(Vector2Subtract(EnemyDefinitePosition, AttackPosition));
	Parallel = { Parallel.y, -Parallel.x };
	for (int i = 1; i <= OutputAttackCount; i++) {
		GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, { EnemyDefinitePosition.x + 45.0f * Parallel.x * i, EnemyDefinitePosition.y + 45.0f * Parallel.y * i }, TowerAttackMovementSpeed, TowerAttackDamage, -1, TowerID, CalcLifespan - 1 * i, RED));
		GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, { EnemyDefinitePosition.x - 45.0f * Parallel.x * i, EnemyDefinitePosition.y - 45.0f * Parallel.y * i }, TowerAttackMovementSpeed, TowerAttackDamage, -1, TowerID, CalcLifespan - 1 * i, RED));
	}
	IsWindUp = false;
}

bool Stark::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;
	Tower::OnUpgrade();
	switch (TowerLevel) {
	case 2:
		TowerCooldown = 90;
		TowerRange = 335.0f;
		TowerAttackDamage = 50.0f;
		TowerAttackMovementSpeed = 7.5f;
		OutputAttackCount = 1;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 85;
		TowerRange = 500.0f;
		TowerAttackDamage = 50.0f;
		TowerAttackMovementSpeed = 7.75f;
		OutputAttackCount = 2;
		TotalCost += 000;
		break;
	}
	return true;
}

void Stark::Update() {
	if (StunTimer) {
		if (StunTimer % 70 == 0) VisualManager::GetInstance().AddVisual(VisualType::TOWER_BIND, TowerBindVisual::TowerBindVisualTemplateBuildAndGet("ui/StunEffect.png", 14, { 48.0f, 112.0f }, { 96.0f, 96.0f }, TowerID));
		StunTimer--;
		return;
	}

	TowerLifespan++;

	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown && !IsWindUp) {
		(this->*OnCooldown)();
		if (IsWindUp) {
			PreviousAttackFrame = TowerLifespan;
		}
	}

	size_t DeltaFire = TowerLifespan - PreviousAttackFrame;
	if (IsWindUp && DeltaFire == 63) {
		(this->*OnCooldown)();
	}

	if (TowerLifespan - PreviousAttackFrame == 70) {
		CurrentAnimationState = ChampionAnimationState::IDLE;
	}
}

void Stark::UpdateAnimation() {

}