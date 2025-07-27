#include "Scout.h"
#include "Utils/ResourceManager.h"

Scout::Scout() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Scout.png"));
	EnemyTextureSize = { 96.0f, 96.0f };

	EnemyFrameStateAmount = 8;
	Scout::UpdateAnimation();

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.78f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Scout::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Scout::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Scout::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	// Cập nhật trạng thái hoạt ảnh
	Scout::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.78f;
}

void Scout::Draw() const {
	DrawTexturePro(*EnemyTexture, { 64.0f * EnemyFrameState, 0.0f, 64.0f * CurrentDirectionType, 64.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Scout::DrawHealthBar();
}

void Scout::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.55f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.55f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}