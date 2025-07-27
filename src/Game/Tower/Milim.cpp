#include "Milim.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include <raymath.h>

Milim::Milim(): Tower() {
	TowerCooldown = 175;
	TowerDeltaCooldown = TowerCooldown / 2;
	TotalCost = 700;
	TowerRange = 600.0f;
	TowerAttackDamage = 100.0f;
	TowerAttackMovementSpeed = 15.0f;

	OnCooldown = &Milim::AttackModule;

	UpgradeColor = { 255, 112, 172, 255 };
}

void Milim::AttackModule() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(TowerPosition);
	size_t CalcLifespan = Vector2Distance(TowerPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(TowerPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, GREEN));
	
	TowerDeltaCooldown = TowerCooldown;
}

void Milim::OnUpgrade() {
	if (TowerLevel == 3) return;	
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerCooldown = 160;
		TowerAttackDamage = 150.0f;
		TowerAttackMovementSpeed = 15.0f;
		TotalCost += 000;
		UpgradeColor = { 255, 71, 157, 255 };
		break;
	case 3:
		TowerCooldown = 140;
		TowerRange = 720.0f;
		TowerAttackDamage = 250.0f;
		TowerAttackMovementSpeed = 20.0f;
		TotalCost += 000;
		UpgradeColor = { 227, 14, 103, 255 };
		break;
	}
}

void Milim::Update() {
	TowerLifespan++;

	if (TowerDeltaCooldown <= 0) (this->*OnCooldown)();
	else TowerDeltaCooldown--;
}

void Milim::UpdateAnimation() {

}

void Milim::Draw() const {
	DrawCircleLines(TowerPosition.x, TowerPosition.y, TowerRange, WHITE);
	DrawCircle(TowerPosition.x, TowerPosition.y, 24.0f, UpgradeColor);
}