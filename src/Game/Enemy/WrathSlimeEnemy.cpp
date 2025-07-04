#include "WrathSlimeEnemy.h"
#include "Utils/AssetManager.h"

WrathSlimeEnemy::WrathSlimeEnemy() {
	Health = BASE_HEALTH;
	Speed = BASE_SPEED;
	CashDrop = BASE_CASH_DROP;
	Used = false;
	SizeFactor = 1.0f;
}

void WrathSlimeEnemy::Update() {
    if (Timer > 0) {
        Timer--;
        SizeFactor += 0.05f;
    }
	Enemy::Update();
	if (FrameTime >= 3) {
		FrameTime = 0;
		FrameState++;
	}
	FrameTime++;
}

void WrathSlimeEnemy::Draw() {
	DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Slime.png"), { 32.0f * FrameState, 32.0f * AnimationState, 32.0f, 32.0f }, { CurrentPosition.x - (32.0f * SizeFactor), CurrentPosition.y - (64.0f * SizeFactor), SizeFactor * 64.0f, SizeFactor * 64.0f}, {0.0f, 0.0f}, 0.0f, RED);
    DrawRectangleLines(CurrentPosition.x - 32.0f, CurrentPosition.y - 64.0f, 64.0f, 64.0f, RED);
}

void WrathSlimeEnemy::OnDamaged(const size_t& _dmg) {
	if (Health <= _dmg) {
		OnDeath();
		Die();
		return;
	}
	if (!Used && Health > BASE_HEALTH / 2 && Health - _dmg <= BASE_HEALTH / 2) {
		Timer = 15;
		Used = true;
        Speed = BASE_SPEED * 2;
        Health = BASE_HEALTH * 3;
	}
	else Health -= _dmg;

}

void WrathSlimeEnemy::DrawHealthBar() {
    DrawRectangle(CurrentPosition.x - 50.0f, CurrentPosition.y - 100.0f * SizeFactor, 100.0f, 5.0f, (Health > BASE_HEALTH) ? BLUE : BLACK);
    if (Health <= BASE_HEALTH) DrawRectangle(CurrentPosition.x - 50.0f, CurrentPosition.y - 100.0f * SizeFactor, 100.0f * Health / BASE_HEALTH, 5.0f, RED);
}