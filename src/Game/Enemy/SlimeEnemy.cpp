#include "SlimeEnemy.h"
#include "Utils/AssetManager.h"
#include <iostream>

SlimeEnemy::SlimeEnemy() {
	WaypointIndex = 0;
	Health = BASE_HEALTH;
	Speed = BASE_SPEED;
	CashDrop = BASE_CASH_DROP;
	Direction = { 0, 0 };
	FrameTime = 0;
	AnimationState = 0;
	FrameState = 0;
}

SlimeEnemy::~SlimeEnemy() {
	Enemy::~Enemy();
}

void SlimeEnemy::SetPosition(const Vector2& _pos) {
	Enemy::SetPosition(_pos);
}

void SlimeEnemy::Update() {
	Enemy::Update();
	if (FrameTime >= 5 * (200 / Speed)) {
		FrameTime = 0;
		++FrameState %= 3;
	}
	else FrameTime++;
}
 
void SlimeEnemy::Draw() {
	DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Slime.png"), {32.0f * FrameState, 32.0f * AnimationState, 32.0f, 32.0f}, {CurrentPosition.x - 32.0f, CurrentPosition.y - 32.0f, 64.0f, 64.0f}, {0.0f, 0.0f}, 0.0f, WHITE);
}

void SlimeEnemy::OnDamaged(const size_t& _damage) {
	Enemy::OnDamaged(_damage);
}

void SlimeEnemy::OnDeath() {
	Enemy::OnDeath();
}

void SlimeEnemy::Die() {
	Enemy::Die();
}