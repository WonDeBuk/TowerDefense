#include "Attack.h"
#include "././Utils/MathUtils.hpp"
#include "Game/VisualManager.h"
#include "GameManager.h"
#include <iostream>

const TextureData Attack::NullTexture = { 0.0f, 0, nullptr };

Attack::~Attack() {}
Attack::Attack() {
	FrameState = 0;
}

void Attack::Update() {}

void Attack::SetAttackID(const int &_AttackID) {
    AttackID = _AttackID;
}

void Attack::AttackKill() {
    GameManager::GetInstance().KillAttack(AttackID);
}