#include "Brawler.h"
#include "Utils/ResourceManager.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual.h"
#include <iostream>

Brawler::Brawler() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Brawler.png"));
	EnemyTextureSize = { 320.0f, 480.0f };

	EnemyFrameStateAmount = 8;
	Brawler::UpdateAnimation();

	AbilityCooldown = 700;

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.91f, EnemyTextureSize.x, EnemyTextureSize.y };

	MaxBounceCount = 2;
}

void Brawler::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Brawler::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Brawler::OnDamage(const float& _Damage) {
	if (EnemyHealth > 0.4f * BASE_HEALTH && EnemyHealth - _Damage <= 0.4f * BASE_HEALTH) {
		MaxBounceCount = 4;
		AbilityCooldown = 300;
	}
	Enemy::OnDamage(_Damage);
		
}

void Brawler::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	float DeltaTime = EnemyLifespan - PreviousAbilityFrame;
	if (!IsAbility && (CurrentBounceCount > 0 || (EnemyHealth <= 1.0f * BASE_HEALTH && GameManager::GetInstance().GetCurrentTowerAmount() > 0 && DeltaTime >= 300))) {
		CurrentSprite = 1;
		EnemyFrameState = -1;
		IsAbility = true;
		EnemyLifespan += 7 - (EnemyLifespan % 7);
		PreviousAbilityFrame = EnemyLifespan;
		EnemySpeed = 0;
		if (CurrentBounceCount == 0) CurrentBounceCount = MaxBounceCount;
	}

	else if (IsAbility) {
		if (DeltaTime == 56) {
			if (CurrentBounceCount == MaxBounceCount) MemoryPosition = EnemyCurrentPosition;
			EnemyCurrentPosition = { -1000.0f, -1000.0f };
		}
		else if (DeltaTime == 70) {
			EnemyFrameState = -1;
			CurrentSprite = 2;	
			FindLanding();	
		}
		else if (DeltaTime == 84) VisualManager::GetInstance().AddVisual(VisualType::PLAIN, Visual::VisualTemplateBuildAndGet("ui/LandingSmoke.png", 12, { EnemyCurrentPosition.x - 225.0f, EnemyCurrentPosition.y - 256.0f }, { 450.0f, 312.0f }, 7));
		
		else if (DeltaTime == 114) {
			PreviousAbilityFrame = EnemyLifespan;
			IsAbility = false;
			if (CurrentBounceCount == 0) {
				EnemySpeed = BASE_SPEED;
				CurrentSprite = 0;
				UpdateDirection();
			}
		}
	}

	// Cập nhật trạng thái hoạt ảnh
	Brawler::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.91f;
}

void Brawler::Draw() const {
	DrawTexturePro(*EnemyTexture, { 256.0f * EnemyFrameState, CurrentSprite * 384.0f, 256.0f * CurrentDirectionType, 384.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Brawler::DrawHealthBar();
}

void Brawler::DrawHealthBar() const {
	if (CurrentBounceCount || EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.25f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.25f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}

void Brawler::FindLanding() {
	GameManager& gm = GameManager::GetInstance();
	EnemyCurrentPosition = MemoryPosition;
	if (CurrentBounceCount == 1 || gm.GetCurrentTowerAmount == 0) {
		CurrentBounceCount = 0;
		return;
	}
	const bool(&TowerPoolAndPlotTracker)[MAX_TOWER_AMOUNT] = gm.GetTowerPlotAndPoolTracker();
	int StartPos = GetRandomValue(0, MAX_TOWER_AMOUNT - 1);
	for (int i = 0; i < MAX_TOWER_AMOUNT; i++) {
		if (TowerPoolAndPlotTracker[StartPos] && !gm.GetTowerByID(StartPos)->IsStunned()) {
			gm.GetTowerByID(StartPos)->ApplyStun(420);
			EnemyCurrentPosition = gm.GetTowerByID(StartPos)->GetTowerPosition();
			
			int Random = GetRandomValue(1, 2);

			EnemyCurrentPosition.x += 50.0f - 100.0f * (Random == 1);

			if (EnemyLifespan % 2) CurrentDirectionType = EnemyDirectionType::FORWARD;
			else CurrentDirectionType = EnemyDirectionType::BACKWARD;
			
			CurrentBounceCount--; 
			return;
		}
		StartPos++;
		StartPos %= MAX_TOWER_AMOUNT;
	}
	CurrentBounceCount = 0;
	return;
}