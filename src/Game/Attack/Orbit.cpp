#include "Orbit.h"
#include "Game/GameManager.h"
#include <raymath.h>
#include <iostream>
#include <cmath>

const Attack* Orbit::OrbitTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _TargetEnemyID, const int& _OwnerID, const float& _StartingAngle, const float& _MaxRadius, const int& _Lifespan, const int& _TotalHit, const HitType& _HitType, const TextureData& _DeathTexture) {
	static Orbit OrbitTemplate;
	OrbitTemplate.GeneralUseVector = _AttackStartPosition;
	OrbitTemplate.AttackCurrentPosition = _AttackStartPosition;
	OrbitTemplate.OwnerID = _OwnerID;
	OrbitTemplate.TargetID = _TargetEnemyID;
	OrbitTemplate.CurrentRadius = Vector2Distance(_AttackStartPosition, _AttackDestinationPosition);
	OrbitTemplate.Angle = _StartingAngle;
	OrbitTemplate.MaxRadius = _MaxRadius;
	OrbitTemplate.AttackMovementSpeed = _AttackMovementSpeed;
	OrbitTemplate.AttackDamage = _AttackDamage;
	OrbitTemplate.Lifespan = _Lifespan;
	OrbitTemplate.TotalHit = _TotalHit;
	OrbitTemplate.AttackTexture = _AttackTexture;
	OrbitTemplate.FrameSize = 1.0f * _AttackTexture.LinkedTexture->width / _AttackTexture.MaxFrameCount;
	OrbitTemplate.DeathTexture = _DeathTexture;
	OrbitTemplate.SetHitType(_HitType);
	return reinterpret_cast<Attack*>(&OrbitTemplate);
}

Orbit::Orbit() {
	PathProgress = 0.0f;
}

void Orbit::Update() {
	Lifespan--;

	std::cout << Lifespan << ' ';
	GameManager& gm = GameManager::GetInstance();

	if (Lifespan <= 0 || gm.GetTowerPlotAndPoolTracker()[OwnerID] == false) {
		Attack::AttackKill();
		return;
	}

	//Check for collision
	if ((this->*CheckForValidHit)() == true) {
		return;
	}

	//Update movement
	if (PathProgress < 1.0f) PathProgress += abs(AttackMovementSpeed) / CurrentRadius;

	if (PathProgress >= 1.0f && gm.GetEnemyPoolTracker()[TargetID]) {
		float Delta = CurrentRadius - Vector2Distance(GeneralUseVector, gm.GetEnemyByID(TargetID)->GetEnemyCurrentPosition());
		if (Delta > abs(AttackMovementSpeed)) CurrentRadius -= abs(AttackMovementSpeed);
		else if (Delta < - abs(AttackMovementSpeed) && CurrentRadius < MaxRadius) CurrentRadius += abs(AttackMovementSpeed);
	}

	if (Lifespan % 5 == 0) FrameState = (FrameState + 1) % AttackTexture.MaxFrameCount;

	AttackCurrentPosition.x = PathProgress * CurrentRadius * cos(Angle) + GeneralUseVector.x;
	AttackCurrentPosition.y = PathProgress * CurrentRadius * sin(Angle) + GeneralUseVector.y;
	Angle -= AttackMovementSpeed * PI / 180.0f;
}

void Orbit::Draw() const {
	float ActualSize = FrameSize * AttackTexture.ScaleFactor;
	DrawTexturePro(*AttackTexture.LinkedTexture, { FrameSize * FrameState, 0.0f, FrameSize, FrameSize }, { AttackCurrentPosition.x, AttackCurrentPosition.y, ActualSize, ActualSize }, { ActualSize / 2, ActualSize / 2 }, Angle, WHITE);
}