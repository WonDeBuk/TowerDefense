#include "Missile.h"
#include "../GameManager.h"
#include "raymath.h"
#include "../Enemy.h"

Missile Missile::MissileTemplate;

const Attack* Missile::MissileTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _ControlPoint1XPercentOffset, const float& _ControlPoint1YPercentOffset, const float& _ControlPoint2XPercentOffset, const float& _ControlPoint2YPercentOffset, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackTargetID, const int& _AttackOwnTowerID) {
    MissileTemplate.AttackStartPosition = _AttackStartPosition;
    MissileTemplate.AttackCurrentPosition = _AttackStartPosition;
    MissileTemplate.AttackDestinationPosition = _AttackDestinationPosition;
    MissileTemplate.ControlPoint1XPercentOffset = _ControlPoint1XPercentOffset;
    MissileTemplate.ControlPoint1YPercentOffset = _ControlPoint1YPercentOffset;
    MissileTemplate.ControlPoint2XPercentOffset = _ControlPoint2XPercentOffset;
    MissileTemplate.ControlPoint2YPercentOffset = _ControlPoint2YPercentOffset;
    MissileTemplate.CurrentPercentage = 0.0f;
    MissileTemplate.Lifespan = 0;
    MissileTemplate.AttackDamage = _AttackDamage;
    MissileTemplate.AttackMovementSpeed = _AttackMovementSpeed;
    MissileTemplate.AttackTargetID = _AttackTargetID;
    MissileTemplate.AttackOwnTowerID = _AttackOwnTowerID;
    Vector2 StartDesVector = Vector2Subtract(_AttackDestinationPosition, _AttackStartPosition);
    Vector2 StartDesPerpendicularVector = {StartDesVector.y, -StartDesVector.x};
    MissileTemplate.ControlPoint1 = Vector2Add(Vector2Add(_AttackStartPosition, Vector2Scale(StartDesVector, _ControlPoint1XPercentOffset)), Vector2Scale(StartDesPerpendicularVector, _ControlPoint1YPercentOffset));
    MissileTemplate.ControlPoint2 = Vector2Add(Vector2Add(_AttackStartPosition, Vector2Scale(StartDesVector, _ControlPoint2XPercentOffset)), Vector2Scale(StartDesPerpendicularVector, _ControlPoint2YPercentOffset));
    return reinterpret_cast<Attack*>(&MissileTemplate);
}

void Missile::UpdateCubicBezierPosition()
{
    float RemainPercentage = 1.0f - CurrentPercentage;
    AttackCurrentPosition = {
        RemainPercentage * RemainPercentage * RemainPercentage * AttackStartPosition.x + 3 * RemainPercentage * RemainPercentage * CurrentPercentage * ControlPoint1.x + 3 * RemainPercentage * CurrentPercentage * CurrentPercentage * ControlPoint2.x + CurrentPercentage * CurrentPercentage * CurrentPercentage * AttackDestinationPosition.x,
        RemainPercentage* RemainPercentage* RemainPercentage* AttackStartPosition.y + 3 * RemainPercentage * RemainPercentage * CurrentPercentage * ControlPoint1.y + 3 * RemainPercentage * CurrentPercentage * CurrentPercentage * ControlPoint2.y + CurrentPercentage * CurrentPercentage * CurrentPercentage * AttackDestinationPosition.y
    };
}

void Missile::Draw() const {
    DrawCircle(AttackCurrentPosition.x, AttackCurrentPosition.y, 4.0f, RED);
}

void Missile::Update() {
	Attack::Update();

    Enemy* TargetEnemy = GameManager::GetInstance().GetEnemyByID(AttackTargetID);
    if (TargetEnemy != nullptr) {
        if (CheckCollisionPointRec(AttackCurrentPosition, TargetEnemy->GetHitBox())) {
            TargetEnemy->OnDamage(AttackDamage);
            Attack::AttackKill();
            return;
        }
    } else {
        if (AttackCurrentPosition == AttackDestinationPosition) {
            Attack::AttackKill();
            return;
        }
    }

    CurrentPercentage += AttackMovementSpeed / Vector2Distance(AttackStartPosition, AttackDestinationPosition);
    Missile::UpdateCubicBezierPosition();
}