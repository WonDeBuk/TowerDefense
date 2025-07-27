#include "Fern.h"
#include "Game/Attack/Split.h"
#include "Game/Attack/Projectile.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual/TowerBindVisual.h"
#include "Utils/ResourceManager.h"
#include <raymath.h>

Fern::Fern(): Tower() {
	CurrentChampion = ChampionType::FERN;
	CurrentAnimationState = ChampionAnimationState::IDLE;
	TowerLifespan = 100;
	TowerCooldown = 135;
	TotalCost = 500;
	TowerRange = 335.0f;
	TowerAttackDamage = 75.0f;
	TowerAttackMovementSpeed = 8.0f;
	SubAttackDamage = 20.0f;
	SubAttackMovementSpeed = 5.0f;
	SubAttackTotalHit = 1;

	OnCooldown = &Fern::AttackModule_1;
}

void Fern::SetTowerID(const int& _TowerID) {
	Tower::SetTowerID(_TowerID);
	AttackPosition = { TowerPosition.x + 52.0f, TowerPosition.y - 96.0f };
}

void Fern::AttackModule_1() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	CurrentAnimationState = ChampionAnimationState::CAST;
	PreviousAttackFrame = TowerLifespan;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	size_t CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet({ 0.8f, 6, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/ElectricAttack.png")) }, AttackPosition, EnemyDefinitePosition, TowerAttackMovementSpeed, TowerAttackDamage, TargetEnemyID, TowerID, CalcLifespan, HitType::TARGETED, { 1.4f, 6, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/ElectricExplosion.png")) }));
}

void Fern::AttackModule_2() {
	(this->*GetTargetEnemy)();
	if (TargetEnemyID == -1) {
		return;
	}

	CurrentAnimationState = ChampionAnimationState::CAST;
	PreviousAttackFrame = TowerLifespan;

	Vector2 EnemyDefinitePosition = GetEnemyDefinitePosition(AttackPosition, TargetEnemyID);
	int CalcLifespan = ceilf(Vector2Distance(AttackPosition, EnemyDefinitePosition) / TowerAttackMovementSpeed);
	int CalcSubLifespan = 0.5f * TowerRange / SubAttackMovementSpeed;
	GameManager::GetInstance().AddAttack(AttackType::SPLIT, Split::SplitTemplateBuildAndGet({ 0.8f, 6, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/ElectricAttack.png")) }, AttackPosition, EnemyDefinitePosition, TowerAttackDamage, TowerAttackMovementSpeed, OutputAttackCount, SubAttackDamage, SubAttackMovementSpeed, SubAttackTotalHit, TargetEnemyID, TowerID, CalcLifespan, CalcSubLifespan, HitType::TARGETED, { 0.5f, 7, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/MiniSparkAttack.png")) }, { 1.4f, 6, const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/ElectricExplosion.png")) }));
}

bool Fern::OnUpgrade() {
	if (TowerLevel == 3) return false;
	TowerLevel++;
	Tower::OnUpgrade();
	switch (TowerLevel) {
	case 2:
		this->OnCooldown = &Fern::AttackModule_2;
		TowerCooldown = 120;
		TowerRange = 375.0f;
		TowerAttackDamage = 100.0f;
		TowerAttackMovementSpeed = 8.5f;
		SubAttackDamage = 80.0f;
		OutputAttackCount = 6;
		TotalCost += 000;
		break;
	case 3:
		TowerCooldown = 75;
		TowerRange = 400.0f;
		TowerAttackDamage = 250.0f;
		TowerAttackMovementSpeed = 8.75f;
		SubAttackDamage = 175.0f;
		SubAttackMovementSpeed = 6.25f;
		SubAttackTotalHit = 2;
		OutputAttackCount = 9;
		TotalCost += 000;
		break;
	}
	return true;
}

void Fern::Update() {
	if (StunTimer) {
		if (StunTimer % 70 == 0) VisualManager::GetInstance().AddVisual(VisualType::TOWER_BIND, TowerBindVisual::TowerBindVisualTemplateBuildAndGet("ui/StunEffect.png", 14, { 48.0f, 112.0f }, { 96.0f, 96.0f }, TowerID));
		StunTimer--;
		return;
	}

	if (TowerLifespan - PreviousAttackFrame >= TowerCooldown) (this->*OnCooldown)();
	else if (TowerLifespan - PreviousAttackFrame >= 21) CurrentAnimationState = ChampionAnimationState::IDLE;

	TowerLifespan++;
}

void Fern::UpdateAnimation() {

}