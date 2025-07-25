#include "Area.h"
#include "Game/GameManager.h"
#include <raymath.h>

const Attack* Area::AreaTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _ExplosionRadius, const float& _AttackDamage, const float& _AttackMovementSpeed, const int& _AttackOwnTowerID, const int& _Lifespan) {
	static Area AreaTemplate;
	AreaTemplate.AttackCurrentPosition = _AttackStartPosition;
	AreaTemplate.AttackDestinationPosition = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPosition));
	AreaTemplate.Lifespan = _Lifespan;
	AreaTemplate.AttackDamage = _AttackDamage;
	AreaTemplate.AttackMovementSpeed = _AttackMovementSpeed;
	AreaTemplate.AttackStartPosition.x = _ExplosionRadius;
	AreaTemplate.AttackOwnTowerID = _AttackOwnTowerID;
	return reinterpret_cast<Attack*> (&AreaTemplate);
}

void Area::Update() {
	Lifespan--;

	if (Lifespan <= 0) {
		OnExpire();
		Attack::AttackKill();
		return;
	}

	AttackCurrentPosition.x += AttackMovementSpeed * AttackDestinationPosition.x;
	AttackCurrentPosition.y += AttackMovementSpeed * AttackDestinationPosition.y;
}

void Area::Draw() const {
	DrawCircle(AttackCurrentPosition.x, AttackCurrentPosition.y, 2.0f, RED);
}

void Area::OnExpire() {
	GameManager& gm = GameManager::GetInstance();
	if (gm.GetCurrentEnemyAmount <= 0) return;
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = gm.GetEnemyByID(i);
			if (CheckCollisionCircleRec(AttackCurrentPosition, AttackStartPosition.x, Object->GetHitBox())) {
				Object->OnDamage(AttackDamage);
			}
		}
	}
}