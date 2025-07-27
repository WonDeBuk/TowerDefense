#include "Revenant.h"
#include "Utils/ResourceManager.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual.h"
#include "Game/Enemy/Bat.h"
#include "Game/Enemy/Pest.h"
#include "Game/Enemy/Hornet.h"
#include <raymath.h>
#include <iostream>

Revenant::Revenant() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Revenant.png"));
	EnemyTextureSize = { 0.8f * 576.0f, 0.8f * 384.0f };

	EnemyFrameStateAmount = 12;
	Revenant::UpdateAnimation();
	SpawnIndex = 0;

	AbilityCooldown = 400;

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.375f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.86f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Revenant::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Revenant::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Revenant::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();
	GameManager& gm = GameManager::GetInstance();
	if (gm.GetEnemyPoolTracker()[EnemyID] == false) return;

	int DeltaTime = EnemyLifespan - PreviousAbilityFrame;
	if (!IsAbility && EnemyHealth <= 1.0f * BASE_HEALTH && DeltaTime >= AbilityCooldown && HeadingWaypointIndex != gm.GetWaypointSize() - 1) {
		CurrentSprite = 1;
		IsAbility = true;
		EnemySpeed = 0;
		EnemyLifespan += 7 - (EnemyLifespan % 7);
		PreviousAbilityFrame = EnemyLifespan;
		EnemyFrameState = -1;
	}
	
	else if (IsAbility) {
		if (DeltaTime == 56) {
			EnemySpeed = BASE_SPEED;
			CurrentSprite = 0;
			WaypointAtSpawnTime = HeadingWaypointIndex;
			WaypointUnit = Vector2Distance(gm.GetWaypointByIndex(HeadingWaypointIndex - 1), gm.GetWaypointByIndex(HeadingWaypointIndex)) / (2.0f * (MAX_SPAWN + 1));
			WaypointDirection = EnemyDirection;
		}
		if (DeltaTime == 56 + SpawnIndex * (112 / MAX_SPAWN)) {
			int Offset = GetRandomValue(SpawnIndex, 2 * MAX_SPAWN - 1) * WaypointUnit;
			int Chance = GetRandomValue(1, 100);
			VisualManager::GetInstance().AddVisual(VisualType::PLAIN, Visual::VisualTemplateBuildAndGet("ui/PopEffect.png", 5, { gm.GetWaypointByIndex(WaypointAtSpawnTime - 1).x + WaypointDirection.x * Offset - 64.0f, gm.GetWaypointByIndex(WaypointAtSpawnTime - 1).y + WaypointDirection.y * Offset - 128.0f }, { 128.0f, 128.0f }));
			if (Chance <= 45) gm.AddEnemy(EnemyType::BAT, Bat::BatTemplateBuildAndGet({ gm.GetWaypointByIndex(WaypointAtSpawnTime - 1).x + WaypointDirection.x * Offset, gm.GetWaypointByIndex(WaypointAtSpawnTime - 1).y + WaypointDirection.y * Offset }, WaypointDirection, WaypointAtSpawnTime));
			else if (Chance <= 90) gm.AddEnemy(EnemyType::PEST, Pest::PestTemplateBuildAndGet({ gm.GetWaypointByIndex(WaypointAtSpawnTime - 1).x + WaypointDirection.x * Offset, gm.GetWaypointByIndex(WaypointAtSpawnTime - 1).y + WaypointDirection.y * Offset }, WaypointDirection, WaypointAtSpawnTime));
			else gm.AddEnemy(EnemyType::HORNET, Hornet::HornetTemplateBuildAndGet({ gm.GetWaypointByIndex(WaypointAtSpawnTime - 1).x + WaypointDirection.x * Offset, gm.GetWaypointByIndex(WaypointAtSpawnTime - 1).y + WaypointDirection.y * Offset }, WaypointDirection, WaypointAtSpawnTime));
			SpawnIndex++;
			if (SpawnIndex >= MAX_SPAWN) {
				SpawnIndex = 0;
				IsAbility = false;
				PreviousAbilityFrame = EnemyLifespan;
			}
		}
	}

	// Cập nhật trạng thái hoạt ảnh
	Revenant::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.375f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.86f;
}

void Revenant::Draw() const {
	DrawTexturePro(*EnemyTexture, { 384.0f * EnemyFrameState, 256.0f * CurrentSprite, 384.0f * CurrentDirectionType, 256.0f }, EnemyDrawbox, { 128.0f * (CurrentDirectionType == BACKWARD), 0.0f}, 0.0f, WHITE);
	Revenant::DrawHealthBar();
}

void Revenant::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.35f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.35f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}