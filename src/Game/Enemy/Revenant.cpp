#include "Revenant.h"
#include "Utils/ResourceManager.h"

Revenant::Revenant() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Revenant.png"));
	EnemyTextureSize = { 576.0f, 384.0f };

	EnemyFrameStateAmount = 12;
	Revenant::UpdateAnimation();

	EnemyHitbox = { EnemyCurrentPosition.x - 48.0f, EnemyCurrentPosition.y - 48.0f, 96.0f, 96.0f };
	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 3 / 8, EnemyCurrentPosition.y - EnemyTextureSize.y * 4 / 5, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Revenant::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}

	// Cập nhật trạng thái hoạt ảnh cho hướng đi trái phải
	if (EnemyDirection.x == 1.0f || EnemyDirection.y == -1.0f) {
		CurrentAnimationState = EnemyAnimationState::FORWARD;
	}
	// Cập nhật trạng thái hoạt ảnh cho hướng đi trên dưới
	else if (EnemyDirection.x == -1.0f || EnemyDirection.y == 1.0f) {
		CurrentAnimationState = EnemyAnimationState::BACKWARD;
	}
}

void Revenant::Update() {
	// Cập nhật lớp cha
	Enemy::Update();

	// Cập nhật trạng thái hoạt ảnh
	Revenant::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyHitbox.x = EnemyCurrentPosition.x - EnemyHitbox.width / 2;
	EnemyHitbox.y = EnemyCurrentPosition.y - EnemyHitbox.height / 2;
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 3 / 8;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 4 / 5;
}

void Revenant::Draw() const {
	DrawTexturePro(*EnemyTexture, { 384.0f * EnemyFrameState, 0.0f, 384.0f * CurrentAnimationState, 256.0f }, EnemyDrawbox, { 144.0f * (CurrentAnimationState == BACKWARD), 0.0f}, 0.0f, WHITE);
	Revenant::DrawHealthBar();
	//DrawRectangleLines(EnemyHitbox.x, EnemyHitbox.y, EnemyHitbox.width, EnemyHitbox.height, RED);
}

void Revenant::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyDrawbox.y + 144.0f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyDrawbox.y + 144.0f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}