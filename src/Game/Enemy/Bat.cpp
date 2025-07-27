#include "Bat.h"
#include "Utils/ResourceManager.h"
#include <iostream>


const Enemy* Bat::BatTemplateBuildAndGet(const Vector2& _EnemyCurrentPosition, const Vector2& _EnemyDirection, const int& _HeadingWaypointIndex) {
	static Bat BatTemplate;
	BatTemplate.HeadingWaypointIndex = _HeadingWaypointIndex;
	BatTemplate.EnemyCurrentPosition = _EnemyCurrentPosition;
	BatTemplate.EnemyDirection = _EnemyDirection;
	BatTemplate.EnemyFrameState = GetRandomValue(0, BatTemplate.EnemyFrameStateAmount - 1);
	BatTemplate.UpdateDirection();
	BatTemplate.UpdateAnimation();
	return reinterpret_cast<Enemy*>(&BatTemplate);
}

Bat::Bat() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Bat.png"));
	EnemyTextureSize = { 128.0f, 128.0f };

	EnemyFrameStateAmount = 8;

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.95f, EnemyTextureSize.x, EnemyTextureSize.y };

	UpdateDirection();
	UpdateAnimation();
}

void Bat::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 4 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Bat::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Bat::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	// Cập nhật trạng thái hoạt ảnh
	Bat::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.95f;
}

void Bat::Draw() const {
	DrawTexturePro(*EnemyTexture, { 160.0f * EnemyFrameState, 0.0f, 160.0f * CurrentDirectionType, 160.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Bat::DrawHealthBar();
}

void Bat::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.7f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.7f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}