#include "Area.h"
#include "Game/GameManager.h"
#include <raymath.h>

const Attack* Area::AreaTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _ExplosionRadius, const float& _AttackDamage, const float& _AttackMovementSpeed, const int& _AttackOwnTowerID, const int& _Lifespan, const HitType& _HitType, const TextureData& _DeathTexture) {
	static Area AreaTemplate;
	AreaTemplate.AttackCurrentPosition = _AttackStartPosition;
	AreaTemplate.GeneralUseVector = Vector2Normalize(Vector2Subtract(_AttackDestinationPosition, _AttackStartPosition));
	AreaTemplate.Lifespan = _Lifespan;
	AreaTemplate.AttackDamage = _AttackDamage;
	AreaTemplate.AttackMovementSpeed = _AttackMovementSpeed;
	AreaTemplate.OwnerID = _AttackOwnTowerID;
	AreaTemplate.AttackTexture = _AttackTexture;
	AreaTemplate.FrameSize = 1.0f * _AttackTexture.LinkedTexture->width / _AttackTexture.MaxFrameCount;
	AreaTemplate.DeathTexture = _DeathTexture;
	AreaTemplate.SetHitType(_HitType);
	return reinterpret_cast<Attack*> (&AreaTemplate);
}

void Area::Update() {
	Lifespan--;

	if (Lifespan <= 0) {
		OnDeath();
		Attack::AttackKill();
		return;
	}

	AttackCurrentPosition.x += AttackMovementSpeed * GeneralUseVector.x;
	AttackCurrentPosition.y += AttackMovementSpeed * GeneralUseVector.y;
}

void Area::Draw() const {
	DrawCircle(AttackCurrentPosition.x, AttackCurrentPosition.y, 2.0f, RED);
}

void Area::OnDeath() {
	GameManager& gm = GameManager::GetInstance();
	int Counter = gm.GetCurrentEnemyAmount();
	if (Counter <= 0) return;
	const bool(&EnemyPoolTracker)[MAX_ENEMY_AMOUNT] = gm.GetEnemyPoolTracker();
	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		if (EnemyPoolTracker[i]) {
			Enemy* Object = gm.GetEnemyByID(i);
			if (CheckCollisionCircleRec(AttackCurrentPosition, ExplosionRadius, Object->GetHitBox())) {
				Object->OnDamage(AttackDamage);
			}
			Counter--;
			if (Counter == 0) return;
		}
	}
}