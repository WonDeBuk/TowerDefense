#include "Frieren.h"
#include "Game/GameManager.h"
#include "Game/Attack/Projectile.h"
#include <raymath.h>
#include "Utils/MathUtils.hpp"
#include <iostream>

Frieren::Frieren(): Tower() {
	TowerCooldown = 90;
	TowerDeltaCooldown = TowerCooldown / 2;
	TotalCost = 350;
	TowerRange = 350.0f;
	TowerAttackDamage = 50.0f;
	TowerAttackMovementSpeed = 5.0f;

	OnCooldown = &Frieren::AttackModule_1;
	
	MaxShotAvailable = 1;
	ShotRemaining = MaxShotAvailable;
	UpgradeColor = { 245, 238, 218, 255 };
}

void Frieren::AttackModule_1() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (ShotRemaining < MaxShotAvailable) { //if burst mode is active and no enemy shows up for 20 frames, reload entirely
			if (TowerDeltaCooldown <= -20) ShotRemaining = MaxShotAvailable;
			else TowerDeltaCooldown--;
		}
		return;
	}

	ShotRemaining--;
	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(TowerPosition);
	size_t CalcLifespan = Vector2Distance(TowerPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(TowerPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, SKYBLUE));

	if (ShotRemaining) {
		TowerDeltaCooldown = 15;
	}
	else {
		TowerDeltaCooldown = TowerCooldown;
		ShotRemaining = MaxShotAvailable;
	}
}

void Frieren::AttackModule_3() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (ShotRemaining < MaxShotAvailable) {
			if (TowerDeltaCooldown <= -15) ShotRemaining = MaxShotAvailable;
			else TowerDeltaCooldown--;
		}
		return;
	}
	
	ShotRemaining--;
	Vector2 TowerOffsetPosition = { TowerPosition.x + GetRandomFloat(-50.0f, 50.0f), TowerPosition.y + GetRandomFloat(-50.0f, 0.0f) };
	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(TowerOffsetPosition);
	size_t CalcLifespan = Vector2Distance(TowerOffsetPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(TowerOffsetPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, BLUE));

	if (ShotRemaining > 0) {
		TowerDeltaCooldown = 15;
	}
	else {
		TowerDeltaCooldown = TowerCooldown;
		ShotRemaining = MaxShotAvailable;
	}
}

void Frieren::OnUpgrade() {
	if (TowerLevel == 3) return; //probably do some pop-up texts that say tower is maxed out or smth
	TowerLevel++;
	
	switch (TowerLevel) {
	case 2:
		TowerCooldown = 70;
		TowerRange = 400.0f;
		TowerAttackDamage = 65.0f;
		TowerAttackMovementSpeed = 6.0f;
		MaxShotAvailable = 2;
		ShotRemaining = MaxShotAvailable;
		TotalCost += 000; //temp value, will come back later
		//game manager do something involves cash here
		UpgradeColor = { 227, 222, 209, 255 };
		break;
	case 3:
		TowerCooldown = 100;
		TowerRange = 475.0f;
		TowerAttackDamage = 125.0f;
		TowerAttackMovementSpeed = 8.5f;
		MaxShotAvailable = 5;
		ShotRemaining = MaxShotAvailable;
		OnCooldown = &Frieren::AttackModule_3;
		TotalCost += 000;
		//
		UpgradeColor = { 196, 195, 190, 255 };
		break;
	}
}

void Frieren::Update() {
	TowerLifespan++;

	if (TowerDeltaCooldown <= 0) (this->*OnCooldown)();
	else TowerDeltaCooldown--;
}

void Frieren::UpdateAnimation() {

}

void Frieren::Draw() const {
	DrawCircleLines(TowerPosition.x, TowerPosition.y, TowerRange, WHITE);
	DrawCircle(TowerPosition.x, TowerPosition.y, 24.0f, UpgradeColor);
}