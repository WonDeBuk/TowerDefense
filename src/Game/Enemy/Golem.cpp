#include "Golem.h"
#include "Utils/ResourceManager.h"
#include "Game/GameManager.h"
#include <raymath.h>
#include <iostream>

Golem::Golem() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyLifespan = GetRandomValue(0, 5) * 120;
	AbilityCooldown = 750;

	PreviousAbilityFrame = 0;
	CurrentSprite = 0;
	IsAbility = false;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Golem.png"));
	EnemyTextureSize = { 200.0f, 200.0f };

	EnemyFrameStateAmount = 8;
	Golem::UpdateAnimation();

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.6f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Golem::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Golem::FindDestination() {
	GameManager& gm = GameManager::GetInstance();
	int TimeJump = 160;
	while (TimeJump > 0 && HeadingWaypointIndex < gm.GetWaypointSize()) {
		EnemyDirection = Vector2Normalize(Vector2Subtract(gm.GetWaypointByIndex(HeadingWaypointIndex), gm.GetWaypointByIndex(HeadingWaypointIndex - 1)));
		float DistanceToWaypoint = Vector2Distance(EnemyCurrentPosition, gm.GetWaypointByIndex(HeadingWaypointIndex));
		int TimeTaken = ceilf(DistanceToWaypoint / BASE_SPEED);
		if (TimeTaken > TimeJump) {
			EnemyCurrentPosition.x += EnemyDirection.x * BASE_SPEED * TimeJump;
			EnemyCurrentPosition.y += EnemyDirection.y * BASE_SPEED * TimeJump;
			TimeJump = 0;
		}
		else {
			TimeJump -= TimeTaken;
			EnemyCurrentPosition = gm.GetWaypointByIndex(HeadingWaypointIndex);
			HeadingWaypointIndex++;
		}
	}
	Enemy::UpdateDirection();
}

void Golem::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 8 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Golem::Update() {
	Enemy::UpdatePosition();
	// Cập nhật lớp cha
	
	if (!IsAbility && EnemyLifespan - PreviousAbilityFrame >= AbilityCooldown) {
		IsAbility = true;
		EnemySpeed = 0.0f;
		CurrentSprite = 1;
		EnemyFrameState = -1;
		EnemyLifespan += (8 - EnemyLifespan % 8);
		PreviousAbilityFrame = EnemyLifespan;
	}

	else if (IsAbility) {
		if (EnemyLifespan - PreviousAbilityFrame == 64) {
			FindDestination();
			CurrentSprite = 2;
		}
		else if (EnemyLifespan - PreviousAbilityFrame == 128) {
			if (HeadingWaypointIndex == GameManager::GetInstance().GetWaypointSize()) {
				EnemyKill();
				return;
			}
			IsAbility = false;
			CurrentSprite = 0;
			EnemySpeed = BASE_SPEED;
			PreviousAbilityFrame = EnemyLifespan;
		}
	}

	// Cập nhật trạng thái hoạt ảnh
	Golem::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.6f;
}

void Golem::Draw() const {
	DrawTexturePro(*EnemyTexture, { 200.0f * EnemyFrameState, 200.0f * CurrentSprite, 200.0f * CurrentDirectionType, 200.0f }, EnemyDrawbox, {0.0f, 0.0f}, 0.0f, WHITE);
	Golem::DrawHealthBar();
}

void Golem::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.45f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.45f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}