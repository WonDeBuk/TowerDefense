#include "Stark.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include <raymath.h>

Stark::Stark() : Tower() {
	CurrentChampion = ChampionType::STARK;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 50;
	TowerCooldown = 70;
	TotalCost = 500;
	TowerRange = 300.0f;
	TowerAttackDamage = 75.0f;
	TowerAttackMovementSpeed = 7.0f;

	OnCooldown = &Stark::AttackModule;
}

void Stark::AttackModule() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	CurrentAnimationState = ChampionAnimationState::CAST;
	PreviousAttackFrame = TowerLifespan;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(TowerPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(TowerPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, ORANGE));
}

bool Stark::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerCooldown = 70;
		TowerRange = 335.0f;
		TowerAttackDamage = 90.0f;
		TowerAttackMovementSpeed = 7.5f;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 70;
		TowerRange = 365.0f;
		TowerAttackDamage = 250.0f;
		TowerAttackMovementSpeed = 7.75f;
		TotalCost += 000;
		break;
	}
	return true;
}

void Stark::Update() {
	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown) (this->*OnCooldown)();
	if (TowerLifespan - PreviousAttackFrame >= 70) CurrentAnimationState = ChampionAnimationState::IDLE;

	TowerLifespan++;
}

void Stark::UpdateAnimation() {

}