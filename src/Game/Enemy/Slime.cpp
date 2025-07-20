#include "Slime.h"
#include "../../Utils/ResourceManager.h"
#include <iostream>

Slime::Slime() {
	// Khởi tạo các attribute
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	// Khởi tạo các properties Texture
	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Slime.png"));
	EnemyTextureSize = {64.0f, 64.0f};

	// Khởi tạo số lượng frame của hoạt ảnh Slime
	EnemyFrameStateAmount = 3;

	// Khởi tạo trạng thái hoạt ảnh bản đầu
	Slime::UpdateAnimation();

	// Khởi tạo Hitbox và Drawbox
	EnemyHitbox = {EnemyCurrentPosition.x - EnemyTextureSize.x / 2, EnemyCurrentPosition.y - EnemyTextureSize.y / 2, EnemyTextureSize.x, EnemyTextureSize.y};
	EnemyDrawbox = {EnemyCurrentPosition.x - EnemyTextureSize.x / 2, EnemyCurrentPosition.y - EnemyTextureSize.y / 2, EnemyTextureSize.x, EnemyTextureSize.y};
}

void Slime::UpdateAnimation() {
    	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) { 
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}


	// Cập nhật trạng thái hoạt ảnh cho hướng đi trái phải
	if (EnemyDirection.x == 1.0f || EnemyDirection.x == -1.0f) {
		CurrentAnimationState = SlimeAnimationState::VERTICAL;
	} 
	// Cập nhật trạng thái hoạt ảnh cho hướng đi trên dưới
	else {
		CurrentAnimationState = SlimeAnimationState::HORIZONTAL;
	}
}

void Slime::Update() {
	// Cập nhật lớp cha
	Enemy::Update();

	// Cập nhật trạng thái hoạt ảnh
	Slime::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyHitbox = {EnemyCurrentPosition.x - EnemyTextureSize.x / 2, EnemyCurrentPosition.y - EnemyTextureSize.y / 2, EnemyTextureSize.x, EnemyTextureSize.y};
	EnemyDrawbox = {EnemyCurrentPosition.x - EnemyTextureSize.x / 2, EnemyCurrentPosition.y - EnemyTextureSize.y / 2, EnemyTextureSize.x, EnemyTextureSize.y};
}
 
void Slime::Draw() const {
	DrawTexturePro(*EnemyTexture, {32.0f * EnemyFrameState, 32.0f * CurrentAnimationState, 32.0f, 32.0f}, EnemyDrawbox, {0.0f, 0.0f}, 0.0f, WHITE);

	Slime::DrawHealthBar();
}

void Slime::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - 100.0f, 100.0f, 5.0f, (EnemyHealth > BASE_HEALTH) ? YELLOW : BLACK);
	if (EnemyHealth < BASE_HEALTH) DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - 100.0f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}