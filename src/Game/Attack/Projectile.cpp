#include "Projectile.h"
#include "../Enemy.h"
#include "raymath.h"
#include "../GameManager.h"
#include "../../Utils/ResourceManager.h"
#include <cmath>
#include <iostream>

const Attack* Projectile::ProjectileTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2 &_AttackStartPositon, const Vector2 &_AttackDestinationPosition, const float &_AttackMovementSpeed, const float &_AttackDamage, const int& _TargetEnemyID, const int& _OwnerID, const int& _Lifespan, const HitType& _HitType, const TextureData& _DeathTexture) {
    static Projectile ProjectileTemplate;
    ProjectileTemplate.AttackCurrentPosition = _AttackStartPositon;
    ProjectileTemplate.AttackMovementSpeed = _AttackMovementSpeed;
    ProjectileTemplate.AttackDamage = _AttackDamage;
    ProjectileTemplate.OwnerID = _OwnerID;
    ProjectileTemplate.TargetID = _TargetEnemyID;
    ProjectileTemplate.GeneralUseVector = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPositon));
    ProjectileTemplate.Lifespan = _Lifespan;
    ProjectileTemplate.AttackTexture = _AttackTexture;
    ProjectileTemplate.DeathTexture = _DeathTexture;
    ProjectileTemplate.FrameSize = 1.0f * _AttackTexture.LinkedTexture->width / _AttackTexture.MaxFrameCount;
    ProjectileTemplate.SetHitType(_HitType);
    return reinterpret_cast<Attack*>(&ProjectileTemplate);
}

void Projectile::Draw() const {
    float ActualSize = FrameSize * AttackTexture.ScaleFactor;
    float Angle = atan2f(GeneralUseVector.y, GeneralUseVector.x) * 180.0f / PI;
    DrawTexturePro(*AttackTexture.LinkedTexture, { FrameSize * FrameState, 0.0f, FrameSize, FrameSize }, { AttackCurrentPosition.x, AttackCurrentPosition.y, ActualSize, ActualSize }, { ActualSize / 2, ActualSize / 2 }, Angle, WHITE);
}

void Projectile::Update() {
    Lifespan--;

    if (Lifespan <= 0) {
        AttackKill();
        return;
    }

    if ((this->*CheckForValidHit)() == true) {
        return;
    }

    if (Lifespan % 5 == 0) FrameState = (FrameState + 1) % AttackTexture.MaxFrameCount;

    AttackCurrentPosition.x += GeneralUseVector.x * AttackMovementSpeed;
    AttackCurrentPosition.y += GeneralUseVector.y * AttackMovementSpeed;
}