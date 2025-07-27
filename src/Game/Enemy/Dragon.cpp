#include "Dragon.h"
#include "Utils/ResourceManager.h"

Dragon::Dragon() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	PreviousAbilityFrame = 0;
	CurrentSprite = 0;
	IsAbility = false;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Dragon.png"));
	EnemyTextureSize = { 256.0f, 256.0f };

	EnemyFrameStateAmount = 6;
	Dragon::UpdateAnimation();

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.97f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Dragon::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Dragon::OnDamage(const float& _Damage) {
	if (EnemyHealth > 0.9f * BASE_HEALTH && EnemyHealth - _Damage <= 0.9f * BASE_HEALTH) {
		IsAbility = true;
		EnemySpeed = 0.0f;
		CurrentSprite = 1;
		EnemyLifespan += (10 - EnemyLifespan % 10);
		EnemyFrameState = 0;
		PreviousAbilityFrame = EnemyLifespan;
	}
	
	Enemy::OnDamage(_Damage);
}

void Dragon::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 10 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Dragon::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	if (IsAbility && EnemyLifespan - PreviousAbilityFrame == 60) {
		IsAbility = false;
		EnemySpeed = 2.5f * BASE_SPEED;
		CurrentSprite = 2;
	}

	// Cập nhật trạng thái hoạt ảnh
	Dragon::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.97f;
}

void Dragon::Draw() const {
	DrawTexturePro(*EnemyTexture, { 144.0f * EnemyFrameState, CurrentSprite * 144.0f, 144.0f * CurrentDirectionType, 144.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Dragon::DrawHealthBar();
}

void Dragon::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.65f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.65f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}