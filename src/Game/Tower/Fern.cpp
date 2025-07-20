#include "Fern.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
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

	OnCooldown = &Fern::AttackModule;
}

void Fern::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x + 52.0f, TowerPosition.y - 96.0f };
}

void Fern::AttackModule() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	CurrentAnimationState = ChampionAnimationState::CAST;
	PreviousAttackFrame = TowerLifespan;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, YELLOW));
}

bool Fern::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerCooldown = 90;
		TowerRange = 335.0f;
		TowerAttackDamage = 90.0f;
		TowerAttackMovementSpeed = 8.5f;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 75;
		TowerRange = 365.0f;
		TowerAttackDamage = 250.0f;
		TowerAttackMovementSpeed = 8.75f;
		TotalCost += 000;
		break;
	}
	return true;
}

void Fern::Update() {
	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown) (this->*OnCooldown)();
	if (TowerLifespan - PreviousAttackFrame >= 35) CurrentAnimationState = ChampionAnimationState::IDLE;

	TowerLifespan++;
}

void Fern::UpdateAnimation() {

}