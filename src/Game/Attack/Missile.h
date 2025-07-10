#pragma once

#include "../Attack.h"
#include "raylib.h"

class Missile: public Attack {
private:
    static Missile MissileTemplate;
    Vector2 ControlPoint1;
    Vector2 ControlPoint2;
    float CurrentPercentage;
    float ControlPoint1XPercentOffset;
    float ControlPoint1YPercentOffset;
    float ControlPoint2XPercentOffset;
    float ControlPoint2YPercentOffset;
public:
    static const Attack* MissileTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _ControlPoint1XPercentOffset, const float& _ControlPoint1YPercentOffset, const float& _ControlPoint2XPercentOffset, const float& _ControlPoint2YPercentOffset, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackTargetID, const int& _AttackOwnTowerID);
    void UpdateCubicBezierPosition();

    void Update() override;
    void Draw() const override;
};