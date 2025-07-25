#include "Frieren.h"
#include "Game/GameManager.h"
#include "Game/Attack/Projectile.h"
#include "Game/VisualManager.h"
#include "Game/Visual/TowerBindVisual.h"
#include <raymath.h>
#include "Utils/MathUtils.hpp"
#include <iostream>
#include <cmath>

Frieren::Frieren(): Tower() {
	CurrentChampion = ChampionType::FRIEREN;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 45;
	TowerCooldown = 70;
	TowerDeltaCooldown = 90;
	TotalCost = 350;
	TowerRange = 350.0f;
	TowerAttackDamage = 25.0f;
	TowerAttackMovementSpeed = 5.0f;

	OnCooldown = &Frieren::AttackModule_1;
}

void Frieren::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x + 44.0f, TowerPosition.y - 96.0f };
}

void Frieren::AttackModule_1() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}
	
	PreviousAttackFrame = TowerLifespan;
	CurrentAnimationState = ChampionAnimationState::CAST;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf((Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed));
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, { 255, 90, 60, 255 }));
}

void Frieren::AttackModule_2() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (TowerLifespan - PreviousAttackFrame + TowerDeltaCooldown >= TowerCooldown * 1.5f) {
			TowerDeltaCooldown = TowerCooldown;
			IsWindUp = false;
		}
		return;
	}

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf((Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed));
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, { 255, 90, 60, 255 }));
	if (!IsWindUp && TowerDeltaCooldown > MIN_COOLDOWN) {
		TowerDeltaCooldown -= MIN_COOLDOWN / 2;
		PreviousAttackFrame = TowerLifespan;
	}
	else {
		IsWindUp = true;
		TowerDeltaCooldown += MIN_COOLDOWN;
	}
	CurrentAnimationState = ChampionAnimationState::CAST;
}

bool Frieren::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;
	Tower::OnUpgrade();
	switch (TowerLevel) {
	case 2:
		TowerCooldown = 60;
		TowerRange = 415.0f;
		TowerAttackDamage = 35.0f;
		TowerAttackMovementSpeed = 7.0f;
		TotalCost += 000; //temp value, will come back later
		//game manager do something involves cash here
        break;
	case 3:
		TowerCooldown = 100;
		TowerRange = 475.0f;
		TowerAttackDamage = 40.0f;
		TowerAttackMovementSpeed = 8.5f;
		OnCooldown = &Frieren::AttackModule_2;
		TotalCost += 000;
		//
        break;
    }
	return true;
}

void Frieren::Update() {
	if (StunTimer) {
		if (StunTimer % 70 == 0) VisualManager::GetInstance().AddVisual(VisualType::TOWER_BIND, TowerBindVisual::TowerBindVisualTemplateBuildAndGet("ui/StunEffect.png", 14, { 48.0f, 112.0f }, { 96.0f, 96.0f }, TowerID));
		StunTimer--;
		return;
	}

	if (TowerLifespan - PreviousAttackFrame >= TowerDeltaCooldown) (this->*OnCooldown)();
	if (!IsWindUp && TowerLifespan - PreviousAttackFrame >= 21) CurrentAnimationState = ChampionAnimationState::IDLE;

	TowerLifespan++;
}
