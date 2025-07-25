#include "Fern.h"
#include "Game/Attack/Projectile.h"
#include "Game/Attack/Split.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual/TowerBindVisual.h"
#include <raymath.h>

Fern::Fern(): Tower() {
	CurrentChampion = ChampionType::FERN;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 100;
	TowerCooldown = 125;
	TotalCost = 500;
	TowerRange = 300.0f;
	TowerAttackDamage = 75.0f;
	TowerAttackMovementSpeed = 8.0f;
	TowerAttackExplosionRadius = 50.0f;

	OnCooldown = &Fern::AttackModule_1;
}

void Fern::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x + 52.0f, TowerPosition.y - 96.0f };
}

void Fern::AttackModule_1() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	CurrentAnimationState = ChampionAnimationState::CAST;
	PreviousAttackFrame = TowerLifespan;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, RED));
}

void Fern::AttackModule_2() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	CurrentAnimationState = ChampionAnimationState::CAST;
	PreviousAttackFrame = TowerLifespan;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::SPLIT, Split::SplitTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackDamage, TowerAttackMovementSpeed, OutputAttackCount, ceilf(0.75f * TowerAttackDamage), 0.75f * TowerRange / TowerAttackMovementSpeed, TargetEnemyID, TowerID, CalcLifespan));
}

bool Fern::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;
	Tower::OnUpgrade();
	switch (TowerLevel) {
	case 2:
		this->OnCooldown = &Fern::AttackModule_2;
		TowerCooldown = 90;
		TowerRange = 335.0f;
		TowerAttackDamage = 100.0f;
		TowerAttackMovementSpeed = 8.5f;
		TowerAttackExplosionRadius = 60.0f;
		OutputAttackCount = 3;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 75;
		TowerRange = 600.0f;
		TowerAttackDamage = 150.0f;
		TowerAttackMovementSpeed = 8.75f;
		TowerAttackExplosionRadius = 100.0f;
		OutputAttackCount = 6;
		TotalCost += 000;
		break;
	}
	return true;
}

void Fern::Update() {
	if (StunTimer) {
		if (StunTimer % 70 == 0) VisualManager::GetInstance().AddVisual(VisualType::TOWER_BIND, TowerBindVisual::TowerBindVisualTemplateBuildAndGet("ui/StunEffect.png", 14, { 48.0f, 112.0f }, { 96.0f, 96.0f }, TowerID));
		StunTimer--;
		return;
	}

	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown) (this->*OnCooldown)();
	else if (TowerLifespan - PreviousAttackFrame >= 35) CurrentAnimationState = ChampionAnimationState::IDLE;

	TowerLifespan++;
}

void Fern::UpdateAnimation() {

}