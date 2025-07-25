#include "Split.h"
#include "Game/GameManager.h"
#include "Game/Attack/Ricochet.h"
#include <raymath.h>

const Attack* Split::SplitTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackDamage, const float& _AttackMovementSpeed, const int& _NumberOfSplit, const float& _InheritDamage, const int& _InheritLifespan, const int& _AttackTargetID, const int& _AttackTowerOwnID, const int& _Lifespan) {
	static Split SplitTemplate;
	SplitTemplate.AttackStartPosition = _AttackStartPosition;
	SplitTemplate.AttackCurrentPosition = _AttackStartPosition;
	SplitTemplate.AttackDestinationPosition = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPosition));
	SplitTemplate.AttackDamage = _AttackDamage;
	SplitTemplate.AttackMovementSpeed = _AttackMovementSpeed;
	SplitTemplate.InheritedDamage = _InheritDamage;
	SplitTemplate.InheritLifespan = _InheritLifespan;
	SplitTemplate.NumberOfSplit = _NumberOfSplit;
	SplitTemplate.Lifespan = _Lifespan;
	SplitTemplate.AttackOwnTowerID = _AttackTowerOwnID;
	SplitTemplate.AttackTargetID = _AttackTargetID;
	return reinterpret_cast<Attack*>(&SplitTemplate);
}

void Split::Update() {
	Lifespan--;

	if (Lifespan <= 0) {
		OnExpire();
		Attack::AttackKill();
		return;
	}

	GameManager& gm = GameManager::GetInstance();
	if (gm.GetEnemyPoolTracker()[AttackTargetID]) {
		Enemy* Object = gm.GetEnemyByID(AttackTargetID);
		if (CheckCollisionPointRec(AttackCurrentPosition, Object->GetHitBox())) {
			OnExpire();
			Object->OnDamage(AttackDamage);
			Attack::AttackKill();
			return;
		}
	}

	AttackCurrentPosition.x += AttackMovementSpeed * AttackDestinationPosition.x;
	AttackCurrentPosition.y += AttackMovementSpeed * AttackDestinationPosition.y;
}

void Split::Draw() const {
	DrawCircle(AttackCurrentPosition.x, AttackCurrentPosition.y, 16.0f, RED);

}

void Split::OnExpire() {
	if (NumberOfSplit <= 0) return;
	float TempAngle = atan2f(AttackCurrentPosition.y - AttackStartPosition.y, AttackCurrentPosition.x - AttackStartPosition.x);
	float Increment = 2.0f * PI / NumberOfSplit;
	for (int i = 0; i < NumberOfSplit; i++) {
		float sine = sin(TempAngle);
		float cosine = cos(TempAngle);
		GameManager::GetInstance().AddAttack(AttackType::RICOCHET, Ricochet::RicochetTemplateBuildAndGet(AttackCurrentPosition, { AttackCurrentPosition.x + 30.0f * cosine, AttackCurrentPosition.y + 30.0f * sine }, AttackMovementSpeed, InheritedDamage, AttackOwnTowerID, InheritLifespan, 2, AttackTargetID));
		TempAngle += Increment;
	}
}