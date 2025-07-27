#include "Attack.h"
#include "././Utils/MathUtils.hpp"
#include "GameManager.h"

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
