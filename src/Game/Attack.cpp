#include "Attack.h"
#include "././Utils/MathUtils.hpp"
#include "GameManager.h"
#include "././Utils/SoundManager.h"

Attack::Attack() {}

void Attack::Update() {
    Lifespan--;
}

void Attack::SetAttackID(const int &_AttackID) {
    AttackID = _AttackID;
}

void Attack::AttackKill() {
    GameManager::GetInstance().KillAttack(AttackID);
}
