#include "Dino.h"
#include "Utils/ResourceManager.h"
#include <iostream>

Dino::Dino() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Dino.png"));
	EnemyTextureSize = { 128.0f, 128.0f };

	PreviousAbilityFrame = 0;
	CurrentSprite = 0;
	IsAbility = false;
	AbilityCooldown = GetRandomValue(75, 225);

	EnemyFrameStateAmount = 5;
	Dino::UpdateAnimation();

	EnemyHitbox = { EnemyCurrentPosition.x - 32.0f, EnemyCurrentPosition.y - 60.0f, 64.0f, 80.0f };
	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.85f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Dino::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Dino::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Dino::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	// Cập nhật trạng thái hoạt ảnh
	Dino::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyHitbox.x = EnemyCurrentPosition.x - EnemyHitbox.width * 0.5f;
	EnemyHitbox.y = EnemyCurrentPosition.y - EnemyHitbox.height * 0.75f;
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.85f;
}

void Dino::Draw() const {
	DrawTexturePro(*EnemyTexture, { 64.0f * EnemyFrameState, 0.0f, 64.0f * CurrentDirectionType, 64.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Dino::DrawHealthBar();
}

void Dino::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.7f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.7f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}