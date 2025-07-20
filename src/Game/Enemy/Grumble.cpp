#include "Grumble.h"
#include "Utils/ResourceManager.h"

Grumble::Grumble() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Grumble.png"));
	EnemyTextureSize = { 256.0f, 256.0f };

	EnemyFrameStateAmount = 10;
	Grumble::UpdateAnimation();

	EnemyHitbox = { EnemyCurrentPosition.x - 32.0f, EnemyCurrentPosition.y - 32.0f, 64.0f, 64.0f };
	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x / 2, EnemyCurrentPosition.y - EnemyTextureSize.y * 3 / 5, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Grumble::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}

	// Cập nhật trạng thái hoạt ảnh cho hướng đi trái phải
	if (EnemyDirection.x == 1.0f) {
		CurrentAnimationState = EnemyAnimationState::FORWARD;
	}
	// Cập nhật trạng thái hoạt ảnh cho hướng đi trên dưới
	else if (EnemyDirection.x == -1.0f) {
		CurrentAnimationState = EnemyAnimationState::BACKWARD;
	}
}

void Grumble::Update() {
	// Cập nhật lớp cha
	Enemy::Update();

	// Cập nhật trạng thái hoạt ảnh
	Grumble::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyHitbox.x = EnemyCurrentPosition.x - EnemyHitbox.width / 2;
	EnemyHitbox.y = EnemyCurrentPosition.y - EnemyHitbox.height / 2;
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x / 2;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 2 / 3;
}

void Grumble::Draw() const {
	DrawTexturePro(*EnemyTexture, { 200.0f * EnemyFrameState, 0.0f, 200.0f * CurrentAnimationState, 200.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Grumble::DrawHealthBar();
}

void Grumble::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyDrawbox.y - 20.0f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyDrawbox.y - 20.0f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}