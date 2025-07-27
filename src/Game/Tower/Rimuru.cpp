#include "Rimuru.h"
#include "Game/Attack/Orbit.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include "Utils/ResourceManager.h"
#include "Game/Visual/TowerBindVisual.h"
#include <raymath.h>
#include <iostream>
#include <cmath>

Rimuru::Rimuru(): Tower() {
	CurrentChampion = ChampionType::RIMURU;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 150;
	TowerCooldown = 400;
	TotalCost = 1500;
	TowerRange = 250.0f;
	TowerAttackDamage = 5.0f;
	TowerAttackMovementSpeed = 4.0f;
	IsWindUp = false;
	OutputAttackCount = 2;
	AttackMaxHit = 3;

	OnCooldown = &Rimuru::AttackModule;
}

void Rimuru::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x, TowerPosition.y };
}

void Rimuru::AttackModule() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (IsWindUp) {
			IsWindUp = false;
		}
		return;
	}
	if (IsWindUp == false) {
		CurrentAnimationState = ChampionAnimationState::CAST;
		IsWindUp = true;
		return;
	}

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	int CalcLifespan = TowerLevel * TowerRange / TowerAttackMovementSpeed;
	float CalcAngle = atan2f(EnemyDefinitePosition.y - AttackPosition.y, EnemyDefinitePosition.x - AttackPosition.x);

	CalcAngle += 1.0f;

	for (int i = 0; i < OutputAttackCount; i++) {
		GameManager::GetInstance().AddAttack(AttackType::ORBIT, Orbit::OrbitTemplateBuildAndGet({3.0f, 8, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/GlaveAttack.png"))}, AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcAngle + i * 2 * PI / OutputAttackCount, TowerRange, CalcLifespan, AttackMaxHit, HitType::OVERRIDE));
	}
	IsWindUp = false;
}

bool Rimuru::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;
	Tower::OnUpgrade();
	switch (TowerLevel) {
	case 2:
		TowerCooldown = 370;
		TowerRange = 280.0f;
		TowerAttackDamage = 15.0f;
		TowerAttackMovementSpeed = 4.0f;
		OutputAttackCount = 3;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 325;
		TowerRange = 325.0f;
		TowerAttackDamage = 30.0f;
		TowerAttackMovementSpeed = 5.0f;
		OutputAttackCount = 5;
		AttackMaxHit = 5;
		TotalCost += 000;
		break;
	}
	return true;
}

void Rimuru::Update() {
	if (StunTimer) {
		if (StunTimer % 70 == 0) VisualManager::GetInstance().AddVisual(VisualType::TOWER_BIND, TowerBindVisual::TowerBindVisualTemplateBuildAndGet("ui/StunEffect.png", 14, { 48.0f, 112.0f }, { 96.0f, 96.0f }, TowerID));
		StunTimer--;
		return;
	}

	TowerLifespan++;

	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown && !IsWindUp) {
		(this->*OnCooldown)();
		if (IsWindUp) {
			PreviousAttackFrame = TowerLifespan;
		}
	}

	size_t DeltaFire = TowerLifespan - PreviousAttackFrame;
	if (IsWindUp && DeltaFire == 49) {
		(this->*OnCooldown)();
	}

	if (DeltaFire == 70) {
		CurrentAnimationState = ChampionAnimationState::IDLE;
	}
}

void Rimuru::UpdateAnimation() {

}
