#include "Stark.h"
#include "Game/Attack/Ricochet.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual/TowerBindVisual.h"
#include "Utils/ResourceManager.h"
#include <raymath.h>

Stark::Stark() : Tower() {
	CurrentChampion = ChampionType::STARK;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 50;
	TowerCooldown = 120;
	TotalCost = 500;
	TowerRange = 300.0f;
	TowerAttackDamage = 75.0f;
	TowerAttackMovementSpeed = 7.0f;
	OutputAttackCount = 0;
	AttackMaxHit = 1;
	OnCooldown = &Stark::AttackModule;
}

void Stark::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x, TowerPosition.y };
	SetTargetType(TargetType::STRONGEST);
}

void Stark::AttackModule() {
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
	GameManager::GetInstance().AddAttack(AttackType::RICOCHET, Ricochet::RicochetTemplateBuildAndGet({2.5f, 8, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/PointyAttack.png"))}, AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TowerID, CalcLifespan, AttackMaxHit, HitType::OVERRIDE));
	Vector2 Parallel = Vector2Normalize(Vector2Subtract(EnemyDefinitePosition, AttackPosition));
	Parallel = { Parallel.y, -Parallel.x };
	for (int i = 1; i <= OutputAttackCount; i++) {
		GameManager::GetInstance().AddAttack(AttackType::RICOCHET, Ricochet::RicochetTemplateBuildAndGet({ 2.5f, 8, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/PointyAttack.png")) }, AttackPosition, { EnemyDefinitePosition.x + 30.0f * Parallel.x * i, EnemyDefinitePosition.y + 30.0f * Parallel.y * i }, TowerAttackMovementSpeed, TowerAttackDamage, TowerID, CalcLifespan, AttackMaxHit, HitType::OVERRIDE));
		GameManager::GetInstance().AddAttack(AttackType::RICOCHET, Ricochet::RicochetTemplateBuildAndGet({ 2.5f, 8, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/PointyAttack.png")) }, AttackPosition, { EnemyDefinitePosition.x - 30.0f * Parallel.x * i, EnemyDefinitePosition.y - 30.0f * Parallel.y * i }, TowerAttackMovementSpeed, TowerAttackDamage, TowerID, CalcLifespan, AttackMaxHit, HitType::OVERRIDE));
	}
	IsWindUp = false;
}

bool Stark::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;
	Tower::OnUpgrade();
	switch (TowerLevel) {
	case 2:
		TowerCooldown = 90;
		TowerRange = 335.0f;
		TowerAttackDamage = 50.0f;
		TowerAttackMovementSpeed = 7.5f;
		OutputAttackCount = 1;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 85;
		TowerRange = 500.0f;
		TowerAttackDamage = 70.0f;
		TowerAttackMovementSpeed = 7.75f;
		OutputAttackCount = 2;
		AttackMaxHit = 2;
		TotalCost += 000;
		break;
	}
	return true;
}

void Stark::Update() {
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
	if (IsWindUp && DeltaFire == 63) {
		(this->*OnCooldown)();
	}

	if (TowerLifespan - PreviousAttackFrame == 70) {
		CurrentAnimationState = ChampionAnimationState::IDLE;
	}
}

void Stark::UpdateAnimation() {

}