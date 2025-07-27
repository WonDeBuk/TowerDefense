#include "Ricochet.h"
#include "../Enemy.h"
#include "raymath.h"
#include "Game/GameManager.h"
#include "../../Utils/ResourceManager.h"
#include <iostream>

const Attack* Ricochet::RicochetTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPositon, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackOwnTowerID, const int& _Lifespan, const int& _TotalPierce, const HitType& _HitType, const int& _Exclusion, const TextureData& _DeathTexture) {
    static Ricochet RicochetTemplate;
    RicochetTemplate.AttackCurrentPosition = _AttackStartPositon;
    RicochetTemplate.AttackMovementSpeed = _AttackMovementSpeed;
    RicochetTemplate.AttackDamage = _AttackDamage;
    RicochetTemplate.OwnerID = _AttackOwnTowerID;
    RicochetTemplate.GeneralUseVector = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPositon));
    RicochetTemplate.Lifespan = _Lifespan;
    RicochetTemplate.AttackTexture = _AttackTexture;
    RicochetTemplate.DeathTexture = _DeathTexture;
    RicochetTemplate.FrameSize = 1.0f * _AttackTexture.LinkedTexture->width / _AttackTexture.MaxFrameCount;
    RicochetTemplate.TotalHit = _TotalPierce;
    RicochetTemplate.StartOfList = 0;
    RicochetTemplate.EndOfList = 0;
    RicochetTemplate.ListSize = 0;
    RicochetTemplate.EnemyBlackList[0].EnemyID = -1;
    if (_Exclusion != -1) {
        RicochetTemplate.EnemyBlackList[0].EnemyID = _Exclusion;
        RicochetTemplate.EnemyBlackList[0].TimeAdded = _Lifespan;
        RicochetTemplate.EndOfList = (RicochetTemplate.EndOfList + 1) % BLACK_LIST_SIZE;
        RicochetTemplate.ListSize = 1;
    }
    RicochetTemplate.SetHitType(_HitType);
    Attack* test = reinterpret_cast<Attack*>(&RicochetTemplate);
    return test;
}

void Ricochet::Draw() const {
    float ActualSize = FrameSize * AttackTexture.ScaleFactor;
    float Angle = atan2f(GeneralUseVector.y, GeneralUseVector.x) * 180.0f / PI;
    DrawTexturePro(*AttackTexture.LinkedTexture, { FrameSize * FrameState, 0.0f, FrameSize, FrameSize }, { AttackCurrentPosition.x, AttackCurrentPosition.y, ActualSize, ActualSize }, { ActualSize / 2, ActualSize / 2 }, Angle, WHITE);
}

void Ricochet::Update() {
    Lifespan--;
    
    if (Lifespan <= 0) {
        AttackKill();
        return;
    }

    GameManager& gm = GameManager::GetInstance();
    if ((this->*CheckForValidHit)() == true) return;

    if (AttackCurrentPosition.x <= 0 || AttackCurrentPosition.x >= 1600) {
        AttackMovementSpeed *= 1.05f;
        GeneralUseVector.x *= -1.0f;
    }
    if (AttackCurrentPosition.y <= 0 || AttackCurrentPosition.y >= 960) {
        AttackMovementSpeed *= 1.05f;
        GeneralUseVector.y *= -1.0f;
    }

    if (Lifespan % 5 == 0) FrameState = (FrameState + 1) % AttackTexture.MaxFrameCount;

    AttackCurrentPosition.x += GeneralUseVector.x * AttackMovementSpeed;
    AttackCurrentPosition.y += GeneralUseVector.y * AttackMovementSpeed;
}