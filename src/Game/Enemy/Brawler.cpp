#include "Brawler.h"
#include "Utils/ResourceManager.h"

Brawler::Brawler() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Brawler.png"));
	EnemyTextureSize = { 320.0f, 480.0f };

	EnemyFrameStateAmount = 8;
	Brawler::UpdateAnimation();
	AnimationIndicator = 0;

	EnemyHitbox = { EnemyCurrentPosition.x - 32.0f, EnemyCurrentPosition.y - 32.0f, 64.0f, 64.0f };
	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x / 2, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.88f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Brawler::UpdateAnimation() {
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

void Brawler::Update() {
	// Cập nhật lớp cha
	Enemy::Update();

	// Cập nhật trạng thái hoạt ảnh
	Brawler::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyHitbox.x = EnemyCurrentPosition.x - EnemyHitbox.width / 2;
	EnemyHitbox.y = EnemyCurrentPosition.y - EnemyHitbox.height / 2;
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x / 2;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.88f;
}

void Brawler::Draw() const {
	DrawTexturePro(*EnemyTexture, { 256.0f * EnemyFrameState, AnimationIndicator * 384.0f, 256.0f * CurrentAnimationState, 384.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Brawler::DrawHealthBar();
}

void Brawler::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyDrawbox.y + EnemyTextureSize.y * 0.6f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyDrawbox.y + EnemyTextureSize.y * 0.6f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}