#include "Milim.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include "Utils/ResourceManager.h"
#include "Game/Visual/TowerBindVisual.h"
#include <raymath.h>
#include <iostream>

Milim::Milim(): Tower() {
	CurrentChampion = ChampionType::MILIM;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 140;
	TowerCooldown = 400;
	TotalCost = 700;
	TowerRange = 500.0f;
	TowerAttackDamage = 100.0f;
	TowerAttackMovementSpeed = 10.0f;
	CurrentShot = 0;
	IsWindUp = false;
	OnCooldown = &Milim::AttackModule;
}

void Milim::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x, TowerPosition.y - 16.0f };
}

void Milim::AttackModule() {
	CurrentShot++;
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (CurrentShot >= OutputAttackCount) {
			IsWindUp = false;
			CurrentShot = 0;
		}
		return;
	}
	if (IsWindUp == false) {
		CurrentAnimationState = ChampionAnimationState::CAST;
		IsWindUp = true;
		return;
	}

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	int CalcLifespan = ceilf(Vector2Distance(EnemyDefinitePosition, AttackPosition) / TowerAttackMovementSpeed) + 5;
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet({ 2.5f, 8, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/StingerAttack.png")) }, AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, HitType::TARGETED));
	if (CurrentShot >= OutputAttackCount) {
		IsWindUp = false;
		CurrentShot = 0;
	}
}

bool Milim::OnUpgrade() {
	if (TowerLevel == 3) return false;	
	TowerLevel++;
	Tower::OnUpgrade();
	switch (TowerLevel) {
	case 2:
		TowerCooldown = 350;
		TowerRange = 575.0f;
		TowerAttackDamage = 150.0f;
		TowerAttackMovementSpeed = 12.5f;
		OutputAttackCount = 2;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 300;
		TowerRange = 675.0f;
		TowerAttackDamage = 250.0f;
		TowerAttackMovementSpeed = 14.0f;
		OutputAttackCount = 3;
		TotalCost += 000;
		break;
	}
	return true;
}

void Milim::Update() {
	if (StunTimer) {
		if (StunTimer % 70 == 0) VisualManager::GetInstance().AddVisual(VisualType::TOWER_BIND, TowerBindVisual::TowerBindVisualTemplateBuildAndGet("ui/StunEffect.png", 14, { 48.0f, 112.0f }, { 96.0f, 96.0f }, TowerID));
		StunTimer--;
		return;
	}

	if (!IsWindUp && TowerLifespan - PreviousAttackFrame >= TowerCooldown) {
		(this->*OnCooldown)();
		if (IsWindUp) {
			CurrentShot = 0;
			PreviousAttackFrame = TowerLifespan;
		}
	}

	size_t DeltaFire = TowerLifespan - PreviousAttackFrame;
	if (IsWindUp && DeltaFire == 49 + CurrentShot * 14 / OutputAttackCount) {
		(this->*OnCooldown)();
	}

	if (TowerLifespan - PreviousAttackFrame == 70) {
		CurrentAnimationState = ChampionAnimationState::IDLE;
	}

	TowerLifespan++;
}
