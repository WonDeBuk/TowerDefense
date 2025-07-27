#include "Rimuru.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include <raymath.h>

Rimuru::Rimuru(): Tower() {
	TowerCooldown = 22;
	TowerDeltaCooldown = TowerCooldown / 2;
	TotalCost = 1500;
	TowerRange = 250.0f;
	TowerAttackDamage = 15.0f;
	TowerAttackMovementSpeed = 10.0f;

	OnCooldown = &Rimuru::AttackModule;

	UpgradeColor = { 163, 208, 255, 255 };
}

void Rimuru::AttackModule() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(TowerPosition);
	size_t CalcLifespan = Vector2Distance(TowerPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(TowerPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, DARKBLUE));

	TowerDeltaCooldown = TowerCooldown;
}

void Rimuru::OnUpgrade() {
	if (TowerLevel == 3) return;
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerCooldown = 14;
		TowerRange = 280.0f;
		TowerAttackDamage = 18.0f;
		TowerAttackMovementSpeed = 10.0f;
		TotalCost += 000;
		UpgradeColor = { 79, 165, 255, 255 };
		break;
	case 3:
		TowerCooldown = 7;
		TowerRange = 325.0f;
		TowerAttackDamage = 23.0f;
		TowerAttackMovementSpeed = 11.0f;
		TotalCost += 000;
		UpgradeColor = { 25, 129, 255, 255 };
		break;
	}
}

void Rimuru::Update() {
	TowerLifespan++;

	if (TowerDeltaCooldown <= 0) (this->*OnCooldown)();
	else TowerDeltaCooldown--;
}

void Rimuru::UpdateAnimation() {

}

void Rimuru::Draw() const {
	DrawCircleLines(TowerPosition.x, TowerPosition.y, TowerRange, WHITE);
	DrawCircle(TowerPosition.x, TowerPosition.y, 24.0f, UpgradeColor);
}