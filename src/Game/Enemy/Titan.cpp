#include "Titan.h"
#include "Game/GameManager.h"
#include "Utils/ResourceManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual/EnemyBindVisual.h"
#include "Game/Visual.h"
#include <raymath.h>
#include <iostream>

Titan::Titan() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Titan.png"));
	EnemyTextureSize = { 240.0f, 240.0f };

	EnemyFrameStateAmount = 10;
	Titan::UpdateAnimation();

	AbilityCooldown = 600;
	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.77f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Titan::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Titan::OnDeath() {
	
}

void Titan::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Titan::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();
	if (GameManager::GetInstance().GetEnemyPoolTracker()[EnemyID] == false) return;

	if (!IsAbility && EnemyLifespan - PreviousAbilityFrame >= AbilityCooldown && EnemyHealth <= 1.0f * BASE_HEALTH && GameManager::GetInstance().GetCurrentAttackAmount() > 0) {
		PreviousAbilityFrame = EnemyLifespan;
		IsAbility = true;
	}

	if (IsAbility) {
		Nullify();
		if (EnemyLifespan - PreviousAbilityFrame == 240) {
			IsAbility = false;
			PreviousAbilityFrame = EnemyLifespan;
		}
		else if ((EnemyLifespan - PreviousAbilityFrame) % 60 == 0) {
			VisualManager::GetInstance().AddVisual(VisualType::ENEMY_BIND, EnemyBindVisual::EnemyBindVisualTemplateBuildAndGet("ui/Forcefield.png", 17, { 114.0f, 174.0f }, { 228.0f, 228.0f }, EnemyID, 5));
		}
	}

	// Cập nhật trạng thái hoạt ảnh
	Titan::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.77f;
}

void Titan::Draw() const {
	DrawTexturePro(*EnemyTexture, { 200.0f * EnemyFrameState, 0.0f, 200.0f * CurrentDirectionType, 200.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Titan::DrawHealthBar();
}

void Titan::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.52f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.52f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}

void Titan::Nullify() {
	GameManager& gm = GameManager::GetInstance();
	if (gm.GetCurrentAttackAmount == 0) return;
	const bool(&AttackPoolTracker)[MAX_ATTACK_AMOUNT] = gm.GetAttackPoolTracker();
	for (int i = 0; i < MAX_ATTACK_AMOUNT; i++) {
		if (AttackPoolTracker[i]) {
			Attack* Object = gm.GetAttackByID(i);
			float Distance = Vector2Distance({ EnemyCurrentPosition.x, EnemyCurrentPosition.y - 60.0f }, gm.GetAttackByID(i)->GetAttackCurrentPosition());
			if (Distance <= BASE_ABILITY_RANGE) {
				VisualManager::GetInstance().AddVisual(VisualType::PLAIN, Visual::VisualTemplateBuildAndGet("ui/Nullify.png", 14, { Object->GetAttackCurrentPosition().x - 48.0f, Object->GetAttackCurrentPosition().y - 48.0f }, { 96.0f, 96.0f }, 3));
				Object->AttackKill(); //this is acceptable as Attack is updated after Enemy
			}
		}
	}
}