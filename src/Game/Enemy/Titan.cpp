#include "Titan.h"
#include "Utils/ResourceManager.h"

Titan::Titan() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Titan.png"));
	EnemyTextureSize = { 364.0f, 364.0f };

	EnemyFrameStateAmount = 10;
	Titan::UpdateAnimation();

	EnemyHitbox = { EnemyCurrentPosition.x - 64.0f, EnemyCurrentPosition.y - 800.0f / 6, 128.0f, 160.0f };
	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x / 2, EnemyCurrentPosition.y - EnemyTextureSize.y * 3 / 5, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Titan::OnDeath() {
	
}

void Titan::UpdateAnimation() {
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

void Titan::Update() {
	// Cập nhật lớp cha
	Enemy::Update();

	// Cập nhật trạng thái hoạt ảnh
	Titan::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyHitbox.x = EnemyCurrentPosition.x - EnemyHitbox.width / 2;
	EnemyHitbox.y = EnemyCurrentPosition.y - EnemyHitbox.height * 5 / 6;
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x / 2;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 5 / 7;
}

void Titan::Draw() const {
	DrawTexturePro(*EnemyTexture, { 200.0f * EnemyFrameState, 0.0f, 200.0f * CurrentAnimationState, 200.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Titan::DrawHealthBar();
}

void Titan::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyDrawbox.y - 20.0f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyDrawbox.y - 20.0f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}