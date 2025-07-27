#include "Frieren.h"
#include "Game/GameManager.h"
#include "Utils/ResourceManager.h"
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
	TowerCooldown = 90;
	TowerLifespan = 45;
	TotalCost = 350;
	TowerRange = 450.0f;
	TowerAttackDamage = 50.0f;
	TowerAttackMovementSpeed = 7.25f;
	Tick = 0;

	OnCooldown = &Frieren::AttackModule_1;
}

void Frieren::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x + 44.0f, TowerPosition.y - 96.0f };
	SetTargetType(TargetType::FIRST);
}

void Frieren::AttackModule_1() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}
	
	PreviousAttackFrame = TowerLifespan;
	CurrentAnimationState = ChampionAnimationState::CAST;
	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	int CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet({2.0f, 8, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/OrbAttack.png"))}, AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, HitType::TARGETED));
}

void Frieren::AttackModule_2() {
	Tick++;
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		if (Tick == MAX_TICK) {
			Tick = 0;
			if (TowerCooldown < 40) TowerCooldown += MIN_COOLDOWN;
		}
		return;
	}

	if (Tick == MAX_TICK) {
		Tick = 0;
		if (TowerCooldown > MIN_COOLDOWN) TowerCooldown -= MIN_COOLDOWN;
	}

	PreviousAttackFrame = TowerLifespan;
	CurrentAnimationState = ChampionAnimationState::CAST;
	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	int CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet({ 2.0f, 8, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/OrbAttack.png")) }, AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, HitType::TARGETED));
}

bool Frieren::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;
	Tower::OnUpgrade();
	switch (TowerLevel) {
	case 2:
		TowerCooldown = 80;
		TowerRange = 460.0f;
		TowerAttackDamage = 70.0f;
		TowerAttackMovementSpeed = 7.75f;
		TotalCost += 000;
        break;
	case 3:
		TowerCooldown = 60;
		TowerRange = 1560.0f;
		TowerAttackDamage = 90.0f;
		TowerAttackMovementSpeed = 8.0f;
		OnCooldown = &Frieren::AttackModule_2;
		TotalCost += 000;
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

	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown) (this->*OnCooldown)();
	if (TowerLifespan - PreviousAttackFrame >= 21) CurrentAnimationState = ChampionAnimationState::IDLE;

	TowerLifespan++;
}
