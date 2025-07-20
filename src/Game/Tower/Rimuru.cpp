#include "Rimuru.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include <raymath.h>
#include <iostream>

Rimuru::Rimuru(): Tower() {
	std::cout << PreviousAttackFrame << '\n';
	CurrentChampion = ChampionType::RIMURU;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 10;
	TowerCooldown = 100;
	TotalCost = 1500;
	TowerRange = 250.0f;
	TowerAttackDamage = 125.0f;
	TowerAttackMovementSpeed = 10.0f;

	OnCooldown = &Rimuru::AttackModule;
}

void Rimuru::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x, TowerPosition.y + 48.0f };
}

void Rimuru::AttackModule() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	CurrentAnimationState = ChampionAnimationState::CAST;
	PreviousAttackFrame = TowerLifespan;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed * 1.5f;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, DARKBLUE));
}

bool Rimuru::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerCooldown = 95;
		TowerRange = 280.0f;
		TowerAttackDamage = 150.0f;
		TowerAttackMovementSpeed = 10.0f;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 80;
		TowerRange = 325.0f;
		TowerAttackDamage = 225.0f;
		TowerAttackMovementSpeed = 8.0f;
		TotalCost += 000;
		break;
	}
	return true;
}

void Rimuru::Update() {
	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown) (this->*OnCooldown)();
	if (TowerLifespan - PreviousAttackFrame >= 70) CurrentAnimationState = ChampionAnimationState::IDLE;

	TowerLifespan++;
}

void Rimuru::UpdateAnimation() {

}
