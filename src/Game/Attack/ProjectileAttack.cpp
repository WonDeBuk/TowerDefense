#include "ProjectileAttack.h"
#include "rlgl.h"
#include "cmath"
#include "Utils/AssetManager.h"

ProjectileAttack::ProjectileAttack(const unsigned int& _dmg, const float& _spd) {
	Damage = _dmg;
	Speed = _spd;
	Lifespan = 0;
	FrameState = 0;
	FrameTime = 0;
}

void ProjectileAttack::Draw() {
	float Angle = atan2f(Direction.y, Direction.x);
	rlPushMatrix();
	rlTranslatef(Origin.x, Origin.y, 0);
	rlRotatef(Angle * 180.0f / PI, 0, 0, 1);
	DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Arrow.png"), { 32.0f * FrameState, 0.0f, 32.0f, 32.0f },
		{ -64.0f, 0, 128.0f, 128.0f }, { 64, 64 }, 0.0f, WHITE);
	//DrawCircle(Origin.x, Origin.y, 32.0f, RED);
	rlPopMatrix();
}

void ProjectileAttack::Update() {
	Attack::Update();
	if (FrameTime >= 3) {
		FrameTime = 0;
		++FrameState %= 3;
	}
	FrameTime++;
}