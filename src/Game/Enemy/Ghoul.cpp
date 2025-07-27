#include "Ghoul.h"
#include "../../Utils/ResourceManager.h"
#include <iostream>

Ghoul::Ghoul() {
	// Khởi tạo các attribute
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	// Khởi tạo các properties Texture
	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Ghoul.png"));
	EnemyTextureSize = { 64.0f, 64.0f };

	// Khởi tạo số lượng frame của hoạt ảnh Ghoul
	EnemyFrameStateAmount = 3;

	// Khởi tạo trạng thái hoạt ảnh bản đầu
	Ghoul::UpdateAnimation();

	// Khởi tạo Hitbox và Drawbox
	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.95f, EnemyTextureSize.x, EnemyTextureSize.y };
}

void Ghoul::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Ghoul::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Ghoul::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	// Cập nhật trạng thái hoạt ảnh
	Ghoul::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyHitbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.95f;
}

void Ghoul::Draw() const {
	DrawTexturePro(*EnemyTexture, { 32.0f * EnemyFrameState, 0.0f, 32.0f * CurrentDirectionType, 32.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);

	Ghoul::DrawHealthBar();
}

void Ghoul::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.5f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.5f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}