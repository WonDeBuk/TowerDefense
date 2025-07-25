#include "Orbit.h"
#include "Game/GameManager.h"
#include <raymath.h>
#include <iostream>
#include <cmath>

Orbit Orbit::OrbitTemplate;

const Attack* Orbit::OrbitTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackEnemyID, const int& _AttackOwnTowerID, const float& _StartingAngle, const float& _MaxRadius, const int& _Lifespan, const int& _TotalPierce) {
	OrbitTemplate.AttackStartPosition = _AttackStartPosition;
	OrbitTemplate.AttackCurrentPosition = _AttackStartPosition;
	OrbitTemplate.AttackDestinationPosition.x = Vector2Distance(_AttackStartPosition, _AttackDestinationPosition);	//the radius
	OrbitTemplate.AttackDestinationPosition.y = _StartingAngle;														//the angle
	OrbitTemplate.MaxRadius = _MaxRadius;
	OrbitTemplate.AttackMovementSpeed = _AttackMovementSpeed;
	OrbitTemplate.AttackDamage = _AttackDamage;
	OrbitTemplate.AttackOwnTowerID = _AttackOwnTowerID;
	OrbitTemplate.Lifespan = _Lifespan;
	OrbitTemplate.TotalPierce = _TotalPierce;
	OrbitTemplate.PathProgress = 0.0f;
	OrbitTemplate.StartOfList = 0;
	OrbitTemplate.EndOfList = 0;
	OrbitTemplate.ListSize = 0;
	return reinterpret_cast<Attack*>(&OrbitTemplate);
}

void Orbit::Update() {
	GameManager& gm = GameManager::GetInstance();
	Lifespan--;

	if (Lifespan <= 0 || gm.GetTowerPlotAndPoolTracker()[AttackOwnTowerID] == false) {
		Attack::AttackKill();
		return;
	}

	//Check for collision
	if (gm.GetCurrentEnemyAmount > 0) {
		const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
		for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
			if (EnemyPoolTracker[i]) {
				if (!Attack::CheckCollisionPierceType(BlackList, LIST_SIZE, StartOfList, EndOfList, ListSize, TotalPierce, i))
					return;
			}
		}
	}

	//Update movement
	if (PathProgress < 1.0f) PathProgress += abs(AttackMovementSpeed) / AttackDestinationPosition.x;
	else if (PathProgress >= 1.0f && gm.GetEnemyPoolTracker()[AttackTargetID]) {
		float DeltaDistance = AttackDestinationPosition.x - Vector2Distance(AttackStartPosition, gm.GetEnemyByID(AttackTargetID)->GetEnemyCurrentPosition());
		if (DeltaDistance > AttackMovementSpeed) AttackDestinationPosition.x -= abs(AttackMovementSpeed);
		else if (DeltaDistance < -AttackMovementSpeed) AttackDestinationPosition.x += abs(AttackMovementSpeed);
	}
	if (AttackDestinationPosition.x > MaxRadius) AttackDestinationPosition.x = MaxRadius;


	AttackCurrentPosition.x = PathProgress * AttackDestinationPosition.x * cos(AttackDestinationPosition.y) + AttackStartPosition.x;
	AttackCurrentPosition.y = PathProgress * AttackDestinationPosition.x * sin(AttackDestinationPosition.y) + AttackStartPosition.y;
	AttackDestinationPosition.y += AttackMovementSpeed * PI / 180.0f;
}

void Orbit::Draw() const {
	DrawCircle(AttackCurrentPosition.x, AttackCurrentPosition.y, 16.0f, RED);
}