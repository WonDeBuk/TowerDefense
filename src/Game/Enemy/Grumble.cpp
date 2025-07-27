#include "Grumble.h"
#include "Utils/ResourceManager.h"

Grumble::Grumble() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Grumble.png"));
	EnemyTextureSize = { 212.0f, 212.0f };

	EnemyFrameStateAmount = 10;
	Grumble::UpdateAnimation();

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.77f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Grumble::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Grumble::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Grumble::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	// Cập nhật trạng thái hoạt ảnh
	Grumble::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.77f;
}

void Grumble::Draw() const {
	DrawTexturePro(*EnemyTexture, { 200.0f * EnemyFrameState, 0.0f, 200.0f * CurrentDirectionType, 200.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Grumble::DrawHealthBar();
}

void Grumble::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.45f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.45f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}