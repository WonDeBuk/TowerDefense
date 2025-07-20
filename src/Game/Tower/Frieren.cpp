#include "Frieren.h"
#include "Game/GameManager.h"
#include "Game/Attack/Projectile.h"
#include <raymath.h>
#include "Utils/MathUtils.hpp"
#include <iostream>
#include <cmath>

Frieren::Frieren(): Tower() {
	CurrentChampion = ChampionType::FRIEREN;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 45;
	TowerCooldown = 90;
	TowerDeltaCooldown = 90;
	TotalCost = 350;
	TowerRange = 350.0f;
	TowerAttackDamage = 25.0f;
	TowerAttackMovementSpeed = 5.0f;

	OnCooldown = &Frieren::AttackModule_1;

	MaxShotAvailable = 1;
	ShotRemaining = MaxShotAvailable;
}

void Frieren::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x + 44.0f, TowerPosition.y - 96.0f };
}

void Frieren::AttackModule_1() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (ShotRemaining < MaxShotAvailable && TowerLifespan - PreviousAttackFrame >= TowerCooldown / 4) {
			ShotRemaining = MaxShotAvailable;
			PreviousAttackFrame = TowerLifespan - TowerDeltaCooldown;
			TowerDeltaCooldown = TowerCooldown;
		}
		return;
	}
	
	PreviousAttackFrame = TowerLifespan;
	CurrentAnimationState = ChampionAnimationState::CAST;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = (Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed) + 5;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, { 255, 90, 60, 255 }));

	ShotRemaining--;
	if (ShotRemaining) {
		TowerDeltaCooldown = 21;
	}
	else {
		TowerDeltaCooldown = TowerCooldown;
		ShotRemaining = MaxShotAvailable;
	}
}

void Frieren::AttackModule_3() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (ShotRemaining < MaxShotAvailable && TowerLifespan - PreviousAttackFrame >= TowerCooldown / 4) {
			ShotRemaining = MaxShotAvailable;
			PreviousAttackFrame = TowerLifespan - TowerDeltaCooldown;
			TowerDeltaCooldown = TowerCooldown;
		}
		return;
	}

	PreviousAttackFrame = TowerLifespan;
	CurrentAnimationState = ChampionAnimationState::CAST;

	Vector2 AttackOffsetPosition = AttackPosition;
	switch (ShotRemaining) {
	case 6:
	case 3:
		AttackOffsetPosition.x -= 30.0f;
		AttackOffsetPosition.y += 10.0f;
		break;
	case 5:
	case 2:
		AttackOffsetPosition.y -= 30.0f;
		break;
	default:
		AttackOffsetPosition.x += 30.0f;
		AttackOffsetPosition.y += 10.0f;
		break;
	}
	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackOffsetPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf(Vector2Distance(AttackOffsetPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(AttackOffsetPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, { (unsigned char)GetRandomValue(175, 255), 0, 0, 255}));

	ShotRemaining--;
	if (ShotRemaining > 0) {
		TowerDeltaCooldown = 14;
	}
	else {
		TowerDeltaCooldown = TowerCooldown;
		ShotRemaining = MaxShotAvailable;
    }
}

bool Frieren::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;

	switch (TowerLevel) {
	case 2:
		TowerCooldown = 70;
		TowerRange = 415.0f;
		TowerAttackDamage = 35.0f;
		TowerAttackMovementSpeed = 7.0f;
		MaxShotAvailable = 2;
		ShotRemaining = MaxShotAvailable;
		TotalCost += 000; //temp value, will come back later
		//game manager do something involves cash here
        break;
	case 3:
		TowerRange = 475.0f;
		TowerAttackDamage = 40.0f;
		TowerAttackMovementSpeed = 8.5f;
		MaxShotAvailable = 6;
		ShotRemaining = MaxShotAvailable;
		OnCooldown = &Frieren::AttackModule_3;
		TotalCost += 000;
		//
        break;
    }
	return true;
}

void Frieren::Update() {
	if (TowerLifespan - PreviousAttackFrame >= TowerDeltaCooldown) (this->*OnCooldown)();
	if (TowerLifespan - PreviousAttackFrame >= 35) CurrentAnimationState = ChampionAnimationState::IDLE;

	TowerLifespan++;
}
