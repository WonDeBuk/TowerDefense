#include "Healbot.h"
#include "Utils/ResourceManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual/EnemyBindVisual.h"
#include "Game/GameManager.h"
#include <raymath.h>

Healbot::Healbot() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Healbot.png"));
	EnemyTextureSize = { 150.0f, 150.0f };

	EnemyFrameStateAmount = 8;
	Healbot::UpdateAnimation();

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.72f, EnemyTextureSize.x, EnemyTextureSize.y };

	EnemyLifespan = 900;
	AbilityCooldown = 1000;
}

void Healbot::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Healbot::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Healbot::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	if (!IsAbility && GameManager::GetInstance().GetCurrentEnemyAmount() > 1 && EnemyLifespan - PreviousAbilityFrame >= AbilityCooldown) {
		IsAbility = true;
		EnemyFrameState = 0;
		EnemyLifespan += 7 - (EnemyLifespan % 7);
		PreviousAbilityFrame = EnemyLifespan;
		CurrentSprite = 1;
		EnemySpeed = 0;
	}

	else if (IsAbility && EnemyLifespan - PreviousAbilityFrame == 56) {
		EnemyFrameState = 0;
		IsAbility = false;
		EnemySpeed = BASE_SPEED;
		CurrentSprite = 0;
		HealTarget();
	}

	// Cập nhật trạng thái hoạt ảnh
	Healbot::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.72f;
}

void Healbot::Draw() const {
	DrawTexturePro(*EnemyTexture, { 96.0f * EnemyFrameState, 96.0f * CurrentSprite, 96.0f * CurrentDirectionType, 96.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Healbot::DrawHealthBar();
}

void Healbot::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.5f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.5f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}

void Healbot::HealTarget() {
	GameManager& gm = GameManager::GetInstance();
	if (gm.GetCurrentEnemyAmount() <= 1) {
		VisualManager::GetInstance().AddVisual(VisualType::ENEMY_BIND, EnemyBindVisual::EnemyBindVisualTemplateBuildAndGet("ui/HealEffect.png", 16, { 78.0f, 124.0f }, { 156.0f, 156.0f }, EnemyID, 3));
		OnHeal(BASE_HEAL / 2);
	}
	else {
		const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
		Enemy* LeastHealth = nullptr;
		for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
			if (EnemyPoolTracker[i]) {
				Enemy* ToCheck = gm.GetEnemyByID(i);
				float Distance = Vector2Distance(ToCheck->GetEnemyCurrentPosition(), EnemyCurrentPosition);
				if (ToCheck != this && Distance <= BASE_HEAL_RANGE && (LeastHealth == nullptr || LeastHealth->GetEnemyHealth() > ToCheck->GetEnemyHealth())) LeastHealth = ToCheck;
			}
		}
		if (LeastHealth) {
			VisualManager::GetInstance().AddVisual(VisualType::ENEMY_BIND, EnemyBindVisual::EnemyBindVisualTemplateBuildAndGet("ui/HealEffect.png", 16, { 78.0f, 124.0f }, { 156.0f, 156.0f }, LeastHealth->GetEnemyID(), 3));
			LeastHealth->OnHeal(BASE_HEAL);
		}
		else {
			VisualManager::GetInstance().AddVisual(VisualType::ENEMY_BIND, EnemyBindVisual::EnemyBindVisualTemplateBuildAndGet("ui/HealEffect.png", 16, { 78.0f, 124.0f }, { 156.0f, 156.0f }, EnemyID, 3));
			OnHeal(BASE_HEAL / 2);
		}
	}
}