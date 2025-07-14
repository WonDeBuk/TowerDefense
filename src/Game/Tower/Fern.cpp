#include "Fern.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include <raymath.h>

Fern::Fern(): Tower() {
	TowerCooldown = 50;
	TowerDeltaCooldown = TowerCooldown / 2;
	TotalCost = 500;
	TowerRange = 300.0f;
	TowerAttackDamage = 75.0f;
	TowerAttackMovementSpeed = 3.0f;

	OnCooldown = &Fern::AttackModule;

	UpgradeColor = { 190, 105, 255, 255 };
}

void Fern::AttackModule() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(TowerPosition);
	size_t CalcLifespan = Vector2Distance(TowerPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(TowerPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, YELLOW));

	TowerDeltaCooldown = TowerCooldown;
}

void Fern::OnUpgrade() {
	if (TowerLevel == 3) return;
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerCooldown = 45;
		TowerRange = 335.0f;
		TowerAttackDamage = 90.0f;
		TowerAttackMovementSpeed = 3.5f;
		TotalCost += 000;
		UpgradeColor = { 179, 79, 255, 255 };
		break;
	case 3:
		TowerCooldown = 30;
		TowerRange = 365.0f;
		TowerAttackDamage = 250.0f;
		TowerAttackMovementSpeed = 3.75f;
		TotalCost += 000;
		UpgradeColor = { 166, 48, 255, 255 };
		break;
	}
}

void Fern::Update() {
	TowerLifespan++;

	if (TowerDeltaCooldown <= 0) (this->*OnCooldown)();
	else TowerDeltaCooldown--;
}

void Fern::UpdateAnimation() {

}

void Fern::Draw() const {
	DrawCircleLines(TowerPosition.x, TowerPosition.y, TowerRange, WHITE);
	DrawCircle(TowerPosition.x, TowerPosition.y, 24.0f, UpgradeColor);
}