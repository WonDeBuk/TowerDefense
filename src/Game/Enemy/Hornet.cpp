#include "Hornet.h"
#include "Game/GameManager.h"
#include "Game/Enemy/Pest.h"
#include "Utils/ResourceManager.h"
#include "Game/VisualManager.h"
#include "Game/Visual.h"

const Enemy* Hornet::HornetTemplateBuildAndGet(const Vector2& _EnemyCurrentPosition, const Vector2& _EnemyDirection, const int& _HeadingWaypointIndex) {
	static Hornet HornetTemplate;
	HornetTemplate.EnemyCurrentPosition = _EnemyCurrentPosition;
	HornetTemplate.EnemyDirection = _EnemyDirection;
	HornetTemplate.HeadingWaypointIndex = _HeadingWaypointIndex;
	HornetTemplate.EnemyFrameState = GetRandomValue(0, HornetTemplate.EnemyFrameStateAmount - 1);
	HornetTemplate.UpdateDirection();
	HornetTemplate.UpdateAnimation();
	return reinterpret_cast<Enemy*>(&HornetTemplate);
}

Hornet::Hornet() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Hornet.png"));
	EnemyTextureSize = { 128.0f, 128.0f };

	EnemyFrameStateAmount = 8;
	Hornet::UpdateAnimation();

	EnemyHitbox = { EnemyCurrentPosition.x - 32.0f, EnemyCurrentPosition.y - 0.8f * 80.0f, 64.0f, 80.0f };
	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.8f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Hornet::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Hornet::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 7 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Hornet::OnDeath() {
	VisualManager::GetInstance().AddVisual(VisualType::PLAIN, Visual::VisualTemplateBuildAndGet("ui/HornetDeath.png", 9, { EnemyCurrentPosition.x - 120.0f, EnemyCurrentPosition.y - 172.0f }, { 240.0f, 240.0f }, 5));
	for (int i = 0; i < 3; i++) {
		GameManager::GetInstance().AddEnemy(EnemyType::PEST, Pest::PestTemplateBuildAndGet({ EnemyCurrentPosition.x - i * 25.0f * EnemyDirection.x, EnemyCurrentPosition.y - i * 25.0f * EnemyDirection.y }, EnemyDirection, HeadingWaypointIndex));
	}
}

void Hornet::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	// Cập nhật trạng thái hoạt ảnh
	Hornet::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyHitbox.x = EnemyCurrentPosition.x - EnemyHitbox.width * 0.5f;
	EnemyHitbox.y = EnemyCurrentPosition.y - EnemyHitbox.height * 0.8f;
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.8f;
}

void Hornet::Draw() const {
	DrawTexturePro(*EnemyTexture, { 256.0f * EnemyFrameState, 0.0f, 256.0f * CurrentDirectionType, 256.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Hornet::DrawHealthBar();}

void Hornet::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.55f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.55f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}