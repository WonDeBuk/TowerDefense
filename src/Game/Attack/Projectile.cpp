#include "Projectile.h"
#include "../Enemy.h"
#include "raymath.h"
#include "../GameManager.h"
#include "././Utils/ResourceManager.h"

Projectile Projectile::ProjectileTemplate;

const Attack* Projectile::ProjectileTemplateBuildAndGet(const Vector2 &_AttackStartPositon, const Vector2 &_AttackDestinationPosition, const float &_AttackMovementSpeed, const float &_AttackDamage, const int &_AttackTargetID, const int &_AttackOwnTowerID) {
    ProjectileTemplate.AttackStartPosition = _AttackStartPositon;
    ProjectileTemplate.AttackDestinationPosition = _AttackDestinationPosition;
    ProjectileTemplate.AttackCurrentPosition = _AttackStartPositon;
    ProjectileTemplate.AttackMovementSpeed = _AttackMovementSpeed;
    ProjectileTemplate.AttackOwnTowerID = _AttackOwnTowerID;
    ProjectileTemplate.AttackTargetID = _AttackTargetID;
    ProjectileTemplate.Lifespan = 0;
    ProjectileTemplate.AttackProjectileDirection = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPositon));
    return reinterpret_cast<Attack*>(&ProjectileTemplate);
}

void Projectile::Draw() const {
    DrawCircle(AttackCurrentPosition.x, AttackCurrentPosition.y, 4.0f, RED);
}

void Projectile::Update() {
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

    AttackCurrentPosition.x += AttackProjectileDirection.x * AttackMovementSpeed;
    AttackCurrentPosition.y += AttackProjectileDirection.y * AttackMovementSpeed;
}