#include "Split.h"
#include "Game/GameManager.h"
#include "Utils/ResourceManager.h"
#include "Game/Attack/Ricochet.h"
#include <raymath.h>
#include <iostream>

const Attack* Split::SplitTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackDamage, const float& _AttackMovementSpeed, const int& _SplitNumber, const float& _SubAttackDamage, const float& _SubAttackMovementSpeed, const int& _SubAttackTotalHit, const int& _TargetEnemyID, const int& _OwnerID, const int& _Lifespan, const int& _SubAttackLifespan, const HitType& _HitType, const TextureData& _SubAttackTexture, const TextureData& _DeathTexture) {
	static Split SplitTemplate;
	SplitTemplate.AttackCurrentPosition = _AttackStartPosition;
	SplitTemplate.GeneralUseVector = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPosition));
	SplitTemplate.AttackDamage = _AttackDamage;
	SplitTemplate.AttackMovementSpeed = _AttackMovementSpeed;
	SplitTemplate.SubAttackDamage = _SubAttackDamage;
	SplitTemplate.SubAttackMovementSpeed = _SubAttackMovementSpeed;
	SplitTemplate.SplitNumber = _SplitNumber;
	SplitTemplate.SubAttackTotalHit = _SubAttackTotalHit;
	SplitTemplate.Lifespan = _Lifespan;
	SplitTemplate.SubAttackLifespan = _SubAttackLifespan;
	SplitTemplate.OwnerID = _OwnerID;
	SplitTemplate.TargetID = _TargetEnemyID;
	SplitTemplate.AttackTexture = _AttackTexture;
	SplitTemplate.FrameSize = 1.0f * _AttackTexture.LinkedTexture->width / _AttackTexture.MaxFrameCount;
	SplitTemplate.SubAttackTexture = _SubAttackTexture;
	SplitTemplate.DeathTexture = _DeathTexture;
	SplitTemplate.SetHitType(_HitType);
	return reinterpret_cast<Attack*>(&SplitTemplate);
}

void Split::Update() {
	Lifespan--;

	if (Lifespan <= 0) {
		Attack::AttackKill();
		return;
	}

	if ((this->*CheckForValidHit)() == true) {
		return;
	}

	if (Lifespan % 6 == 0) FrameState = (FrameState + 1) % AttackTexture.MaxFrameCount;

	AttackCurrentPosition.x += AttackMovementSpeed * GeneralUseVector.x;
	AttackCurrentPosition.y += AttackMovementSpeed * GeneralUseVector.y;
}

void Split::Draw() const {
	float ActualSize = FrameSize * AttackTexture.ScaleFactor;
	float Angle = atan2f(GeneralUseVector.y, GeneralUseVector.x) * 180.0f / PI;
	DrawTexturePro(*AttackTexture.LinkedTexture, { FrameSize * FrameState, 0.0f, FrameSize, FrameSize }, { AttackCurrentPosition.x, AttackCurrentPosition.y, ActualSize, ActualSize }, { ActualSize / 2, ActualSize / 2 }, Angle, WHITE);
}

void Split::OnDeath() {
	Attack::OnDeath();

	if (SplitNumber <= 0) return;
	float TempAngle = atan2f(GeneralUseVector.y, GeneralUseVector.x);
	float Increment = 2.0f * PI / SplitNumber;
	GameManager::GetInstance().AddAttack(AttackType::RICOCHET, Ricochet::RicochetTemplateBuildAndGet(SubAttackTexture, AttackCurrentPosition, { AttackCurrentPosition.x + 30.0f * cos(TempAngle), AttackCurrentPosition.y + 30.0f * sin(TempAngle) }, SubAttackMovementSpeed, SubAttackDamage, OwnerID, SubAttackLifespan, SubAttackTotalHit, HitType::OVERRIDE, TargetID));
	if (SplitNumber % 2 == 0) {
		GameManager::GetInstance().AddAttack(AttackType::RICOCHET, Ricochet::RicochetTemplateBuildAndGet(SubAttackTexture, AttackCurrentPosition, { AttackCurrentPosition.x + 30.0f * cos(TempAngle + PI), AttackCurrentPosition.y + 30.0f * sin(TempAngle + PI) }, SubAttackMovementSpeed, SubAttackDamage, OwnerID, SubAttackLifespan, SubAttackTotalHit, HitType::OVERRIDE, TargetID, Attack::NullTexture));
		SplitNumber--;
	}
	SplitNumber = (SplitNumber - 1) / 2;
	for (int i = 1; i <= SplitNumber; i++) {
		GameManager::GetInstance().AddAttack(AttackType::RICOCHET, Ricochet::RicochetTemplateBuildAndGet(SubAttackTexture, AttackCurrentPosition, { AttackCurrentPosition.x + 30.0f * cos(TempAngle + i * Increment), AttackCurrentPosition.y + 30.0f * sin(TempAngle + i * Increment) }, SubAttackMovementSpeed, SubAttackDamage, OwnerID, SubAttackLifespan, SubAttackTotalHit, HitType::OVERRIDE, TargetID));
		GameManager::GetInstance().AddAttack(AttackType::RICOCHET, Ricochet::RicochetTemplateBuildAndGet(SubAttackTexture, AttackCurrentPosition, { AttackCurrentPosition.x + 30.0f * cos(TempAngle - i * Increment), AttackCurrentPosition.y + 30.0f * sin(TempAngle - i * Increment) }, SubAttackMovementSpeed, SubAttackDamage, OwnerID, SubAttackLifespan, SubAttackTotalHit, HitType::OVERRIDE, TargetID));
	}
}