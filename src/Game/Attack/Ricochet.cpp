#include "Ricochet.h"
#include "../Enemy.h"
#include "raymath.h"
#include "Game/GameManager.h"
#include "../../Utils/ResourceManager.h"

Ricochet Ricochet::RicochetTemplate;

const Attack* Ricochet::RicochetTemplateBuildAndGet(const Vector2& _AttackStartPositon, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackOwnTowerID, const int& _Lifespan, const int& _TotalPierce, int _Exclusion) {
    RicochetTemplate.AttackStartPosition = _AttackStartPositon;
    RicochetTemplate.AttackCurrentPosition = _AttackStartPositon;
    RicochetTemplate.AttackMovementSpeed = _AttackMovementSpeed;
    RicochetTemplate.AttackDamage = _AttackDamage;
    RicochetTemplate.AttackOwnTowerID = _AttackOwnTowerID;
    RicochetTemplate.AttackTargetID = -1;
    RicochetTemplate.AttackRicochetDirection = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPositon));
    RicochetTemplate.Lifespan = _Lifespan;
    RicochetTemplate.TotalPierce = _TotalPierce;
    RicochetTemplate.StartOfList = 0;
    RicochetTemplate.EndOfList = 0;
    RicochetTemplate.ListSize = 0;
    RicochetTemplate.BlackList[0].EnemyID = -1;
    if (_Exclusion != -1) {
        RicochetTemplate.BlackList[RicochetTemplate.EndOfList].EnemyID = _Exclusion;
        RicochetTemplate.BlackList[RicochetTemplate.EndOfList].TimeAdded = _Lifespan;
        RicochetTemplate.EndOfList = (RicochetTemplate.EndOfList + 1) % LIST_SIZE;
        RicochetTemplate.ListSize = 1;
    }
    RicochetTemplate.AttackDestinationPosition.x = 1; //decay speed
    return reinterpret_cast<Attack*>(&RicochetTemplate);
}

void Ricochet::Draw() const {
    DrawCircle(AttackCurrentPosition.x, AttackCurrentPosition.y, 8.0f, BLUE);
}

void Ricochet::Update() {
    Lifespan --;
    if (Lifespan <= 0) {
        AttackKill();
        return;
    }

    GameManager& gm = GameManager::GetInstance();
    if (gm.GetCurrentEnemyAmount > 0) {
        const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
        for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
            if (EnemyPoolTracker[i]) {
                if (!Attack::CheckCollisionPierceType(BlackList, LIST_SIZE, StartOfList, EndOfList, ListSize, TotalPierce, i))
                    return;
            }
        }
    }

    if (AttackCurrentPosition.x <= 0 || AttackCurrentPosition.x >= 1600) {
        AttackMovementSpeed *= 1.05f;
        AttackRicochetDirection.x *= -1.0f;
    }
    if (AttackCurrentPosition.y <= 0 || AttackCurrentPosition.y >= 960) {
        AttackMovementSpeed *= 1.05f;
        AttackRicochetDirection.y *= -1.0f; 
    }

    AttackCurrentPosition.x += AttackRicochetDirection.x * AttackMovementSpeed;
    AttackCurrentPosition.y += AttackRicochetDirection.y * AttackMovementSpeed;
}