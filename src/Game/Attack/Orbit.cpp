#include "Orbit.h"
#include "Game/GameManager.h"
#include <cmath>

const Attack* Orbit::OrbitTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _TargetEnemyID, const int& _AttackOwnTowerID, const size_t& _Lifespan, const int& _TimeToDestination) {
	OrbitTemplate.AttackStartPosition = _AttackStartPosition;
	OrbitTemplate.AttackCurrentPosition = _AttackStartPosition;
	OrbitTemplate.AttackDestinationPosition = _AttackDestinationPosition;
	OrbitTemplate.AttackMovementSpeed = _AttackMovementSpeed;
	OrbitTemplate.AttackDamage = _AttackDamage;
	OrbitTemplate.TargetEnemyID = _TargetEnemyID;
	OrbitTemplate.AttackOwnTowerID = _AttackOwnTowerID;
	OrbitTemplate.Lifespan = _Lifespan;
	float Radius
	OrbitTemplate.BlackListSize = 0;
	return reinterpret_cast<Attack*>(&OrbitTemplate);
}

void Orbit::Update() {
	if (Lifespan <= 0) {
		GameManager::GetInstance().KillAttack(AttackID);
		return;
	}


}

void Orbit::Draw() {

}