#include "SlimeEnemy.h"
#include "Utils/AssetManager.h"
#include <iostream>

SlimeEnemy::SlimeEnemy() {
	Health = BASE_HEALTH;
	Speed = BASE_SPEED;
	CashDrop = BASE_CASH_DROP;
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

void SlimeEnemy::DrawHealthBar() {
	if (Health == BASE_HEALTH) return;
	DrawRectangle(CurrentPosition.x - 50.0f, CurrentPosition.y - 100.0f, 100.0f, 5.0f, (Health > BASE_HEALTH) ? YELLOW : BLACK);
	if (Health < BASE_HEALTH) DrawRectangle(CurrentPosition.x - 50.0f, CurrentPosition.y - 100.0f, 100.0f * Health / BASE_HEALTH, 5.0f, RED);
}