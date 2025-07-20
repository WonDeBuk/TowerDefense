#include "Projectile.h"
#include "../Enemy.h"
#include "raymath.h"
#include "../GameManager.h"
#include "../../Utils/ResourceManager.h"

Projectile Projectile::ProjectileTemplate;

const Attack* Projectile::ProjectileTemplateBuildAndGet(const Vector2 &_AttackStartPositon, const Vector2 &_AttackDestinationPosition, const float &_AttackMovementSpeed, const float &_AttackDamage, const int &_AttackTargetID, const int &_AttackOwnTowerID, const size_t& _Lifespan, const Color& _AttackColor) {
    ProjectileTemplate.AttackStartPosition = _AttackStartPositon;
    ProjectileTemplate.AttackDestinationPosition = _AttackDestinationPosition;
    ProjectileTemplate.AttackCurrentPosition = _AttackStartPositon;
    ProjectileTemplate.AttackMovementSpeed = _AttackMovementSpeed;
    ProjectileTemplate.AttackDamage = _AttackDamage;
    ProjectileTemplate.AttackOwnTowerID = _AttackOwnTowerID;
    ProjectileTemplate.AttackTargetID = _AttackTargetID;
    ProjectileTemplate.AttackProjectileDirection = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPositon));
    ProjectileTemplate.Lifespan = _Lifespan;
    ProjectileTemplate.AttackColor = _AttackColor;
    return reinterpret_cast<Attack*>(&ProjectileTemplate);
}

void Projectile::Draw() const {
    DrawCircle(AttackCurrentPosition.x, AttackCurrentPosition.y, 8.0f, AttackColor);
}

void Projectile::Update() {
    if (!Lifespan) {
        AttackKill();
        return;
    }
    
    Attack::Update();

    Enemy* TargetEnemy = GameManager::GetInstance().GetEnemyByID(AttackTargetID);
    if (TargetEnemy != nullptr) {
        if (CheckCollisionPointRec(AttackCurrentPosition, TargetEnemy->GetHitBox())) {
            TargetEnemy->OnDamage(AttackDamage);
            Attack::AttackKill();
            return;
        }
    }

    AttackCurrentPosition.x += AttackProjectileDirection.x * AttackMovementSpeed;
    AttackCurrentPosition.y += AttackProjectileDirection.y * AttackMovementSpeed;
}