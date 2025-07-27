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
	EnemyDrawbox = {EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.95f, EnemyTextureSize.x, EnemyTextureSize.y};
}

void Slime::UpdateAnimation() {
    // Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) { 
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Slime::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Slime::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	// Cập nhật trạng thái hoạt ảnh
	Slime::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.95f;
}
 
void Slime::Draw() const {
	DrawTexturePro(*EnemyTexture, {32.0f * EnemyFrameState, 0.0f, 32.0f * CurrentDirectionType, 32.0f}, EnemyDrawbox, {0.0f, 0.0f}, 0.0f, WHITE);

	Slime::DrawHealthBar();
	DrawHitboxAndPivot();
}

void Slime::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.5f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.5f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}