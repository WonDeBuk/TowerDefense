#include "Pest.h"
#include "Game/GameManager.h"
#include "Utils/ResourceManager.h"
#include <iostream>

const Enemy* Pest::PestTemplateBuildAndGet(const Vector2& _EnemyCurrentPosition, const Vector2& _EnemyDirection, const int& _HeadingWaypointIndex) {
	static Pest PestTemplate;
	PestTemplate.EnemyCurrentPosition = _EnemyCurrentPosition;
	PestTemplate.EnemyDirection = _EnemyDirection;
	PestTemplate.HeadingWaypointIndex = _HeadingWaypointIndex;
	PestTemplate.EnemyFrameState = GetRandomValue(0, PestTemplate.EnemyFrameStateAmount - 1);
	PestTemplate.UpdateDirection();
	PestTemplate.UpdateAnimation();
	return reinterpret_cast<Enemy*>(&PestTemplate);
}

Pest::Pest() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Pest.png"));
	EnemyTextureSize = { 128.0f, 128.0f };

	EnemyFrameStateAmount = 8;
	Pest::UpdateAnimation();

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.8f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Pest::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Pest::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Pest::OnDeath() {

}

void Pest::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	// Cập nhật trạng thái hoạt ảnh
	Pest::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.8f;
}

void Pest::Draw() const {
	DrawTexturePro(*EnemyTexture, { 256.0f * EnemyFrameState, 0.0f, 256.0f * CurrentDirectionType, 256.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Pest::DrawHealthBar();
}

void Pest::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.55f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.55f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}